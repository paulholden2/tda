FILE(
	GLOB
	FS_HEADER_FILES
	${TDA_INCLUDE_DIR}/tda/fs/*.h
	${TDA_INCLUDE_DIR}/tda/fs.h
	*.h
	)

FILE(
	GLOB
	FS_SOURCE_FILES
	*.c
	)

ADD_LIBRARY(
	TDA_fs
	${FS_HEADER_FILES}
	${FS_SOURCE_FILES}
	)

TARGET_LINK_LIBRARIES(TDA_fs TDA_lib_physfs)
