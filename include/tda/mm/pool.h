#ifndef TDA_MM_POOL_H
#define TDA_MM_POOL_H

#include <stddef.h>

int pool_init(int argc, const char *argv[]);

void pool_deinit(void);

int pool_is_init(void);

void *pool_malloc(size_t sz);

void *pool_calloc(size_t num, size_t sz);

void *pool_realloc(void *ptr, size_t sz);

void pool_free(void *ptr);

#endif /* TDA_MM_POOL_H */
