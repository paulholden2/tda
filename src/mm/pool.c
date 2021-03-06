#include <string.h>
#include <tda/mm/stack.h>
#include <tda/mm/pool.h>

#define ENABLE_POOL_LOG 1

#if ENABLE_POOL_LOG
#include <stdio.h>
#endif

#define MIN_BLOCK_SIZE_ORDER     4
#define MIN_SECTOR_COUNT_ORDER   3
#define DEFAULT_SECTOR_ORDER     20

/* Each block must have at least sizeof(void *) bytes (for the free chain) */
#if MIN_BLOCK_SIZE_ORDER < 3
#error "Pool allocator - Invalid minimum block size"
#endif

struct pool_sector
{
	void    *buffer;
	void    *front;
	size_t   block_size;
	int      block_count;
	int      id;
};

static int sector_block_count(int order);
static int sector_block_size(int order);
static struct pool_sector *create_pool_sector(int order);
static void delete_pool_sector(struct pool_sector *sec);
static void init(struct pool_sector *sec);
static int release_block(struct pool_sector *sec, void *ptr);
static int valid_block(struct pool_sector *sec, void *ptr);
static int free_block(struct pool_sector *sec, void *ptr);
static int prepend_empty(struct pool_sector *sec, void *ptr);
static int prepend(struct pool_sector *sec, void *ptr);
static int append_free(struct pool_sector *sec, void *ptr);
static void check(struct pool_sector *sec);

static struct pool_sector **sectors;
static int                  num_sectors;

static int is_init;

int pool_init(int argc, const char *argv[])
{
	int i;

	num_sectors = DEFAULT_SECTOR_ORDER - MIN_BLOCK_SIZE_ORDER;

	sectors = stack_malloc(num_sectors * sizeof(*sectors));
	if (!sectors)
		return 0;

	for (i = 0; i < num_sectors; ++i) {
		sectors[i] = create_pool_sector(MIN_BLOCK_SIZE_ORDER + i);
		if (!sectors[i])
			pool_deinit();
	}

	is_init = 1;

	return 1;
}

void pool_deinit(void)
{
	int i;

	if (!sectors)
		return;

	for (i = 0; i < num_sectors; ++i) {
		if (sectors[i]) {
			check(sectors[i]);
			delete_pool_sector(sectors[i]);
		}
	}

	stack_free(sectors);

	is_init = 0;
}

int pool_is_init(void)
{
	return is_init;
}

void *pool_malloc(size_t sz)
{
	void *ptr;
	int i;

	for (i = 0; i < num_sectors; ++i) {
		if (!sectors[i] || sectors[i]->block_size < sz)
			continue;

		if (sectors[i]->front) {
			ptr = sectors[i]->front;

			sectors[i]->front = *(void **)sectors[i]->front;

			return ptr;
		}
	}

	return 0;
}

void *pool_calloc(size_t num, size_t sz)
{
	void *ptr;

	sz *= num;

	ptr = pool_malloc(sz);
	if (!ptr)
		return 0;

	return memset(ptr, 0, sz);
}

void *pool_realloc(void *ptr, size_t sz)
{
	void *newptr;

	if (!ptr && sz)
		return pool_malloc(sz);

	if (ptr && !sz) {
		pool_free(ptr);

		return 0;
	}

	newptr = pool_malloc(sz);
	if (!newptr)
		return 0;

	pool_free(ptr);

	return newptr;
}

void pool_free(void *ptr)
{
	int i;

	for (i = 0; i < num_sectors; ++i) {
		if (release_block(sectors[i], ptr))
			break;
	}
}

int sector_block_count(int order)
{
	order = DEFAULT_SECTOR_ORDER - order;

	if (order < MIN_SECTOR_COUNT_ORDER)
		order = MIN_SECTOR_COUNT_ORDER;

	return 1 << order;
}

int sector_block_size(int order)
{
	if (order < MIN_BLOCK_SIZE_ORDER)
		order = MIN_BLOCK_SIZE_ORDER;

	return 1 << order;
}

struct pool_sector *create_pool_sector(int order)
{
	int count, size;
	struct pool_sector *sec;
	void *buffer;
	
	count = sector_block_count(order);
	size  = sector_block_size(order);

	sec = stack_malloc(sizeof(*sec));
	buffer = stack_malloc(count * size);

	if (!sec || !buffer) {
		stack_free(buffer);
		stack_free(sec);

		return 0;
	}
	
	sec->id = order - MIN_BLOCK_SIZE_ORDER;
	sec->block_count  = count;
	sec->block_size   = size;
	sec->buffer       = buffer;

	init(sec);

	if (ENABLE_POOL_LOG) {
		printf("pool: created sector %2d, blocks %-6d size %-6d\n",
		       sec->id, sec->block_count, sec->block_size);
	}

	return sec;
}

void delete_pool_sector(struct pool_sector *sec)
{
	stack_free(sec->buffer);
	stack_free(sec);

	if (ENABLE_POOL_LOG)
		printf("pool: deleted sector %d\n", sec->id);
}

void init(struct pool_sector *sec)
{
	int i;
	void **ptr;
	char *next;

	sec->front = sec->buffer;

	ptr = (void **)sec->buffer;

	for (i = 0; i < sec->block_count - 1; ++i) {
		next = (char *)ptr + sec->block_size;
		*ptr = (void **)next;
		ptr  = (void **)next;
	}

	*ptr = 0;
}

int release_block(struct pool_sector *sec, void *ptr)
{
	if (!valid_block(sec, ptr))
		return 0;

	return free_block(sec, ptr);
}

int valid_block(struct pool_sector *sec, void *ptr)
{
	ptrdiff_t tmp = (ptrdiff_t)ptr - (ptrdiff_t)sec->buffer;
	ptrdiff_t sz  = (ptrdiff_t)(sec->block_size * sec->block_count);
	
	if (tmp < 0 || tmp >= sz || tmp % (ptrdiff_t)sec->block_size)
		return 0;
	else
		return 1;
}

int free_block(struct pool_sector *sec, void *ptr)
{
	if (!sec->front)
		prepend_empty(sec, ptr);
	else if (ptr < sec->front)
		prepend(sec, ptr);
	else
		append_free(sec, ptr);

	return 1;
}

int prepend_empty(struct pool_sector *sec, void *ptr)
{
	sec->front = ptr;

	*(void **)ptr = 0;

	return 1;
}

int prepend(struct pool_sector *sec, void *ptr)
{
	*(void **)ptr = sec->front;

	sec->front = ptr;

	return 1;
}

int append_free(struct pool_sector *sec, void *ptr)
{
	void *cur, *next;

	cur = sec->front;
	do {
		next = *(void **)cur;
	} while (next && next < ptr);

	*(void **)cur = ptr;
	*(void **)ptr = next;

	return 1;
}

void check(struct pool_sector *sec)
{
	int i;
	void *p1, *p2;

	for (i = 0; i < sec->block_count - 1; ++i) {
		p1 = (char *)sec->buffer + sec->block_size * i;
		p2 = (char *)p1 + sec->block_size;

		if (*(void **)p1 != p2) {
			printf("pool: block 0x%X leaked in sector %d\n",
			       p1, sec->id);
		}
	}
}
