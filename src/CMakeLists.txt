#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ZZIDUO_SRC)

set(ZZIDUO_SRC
	thread_pool.cc
	sample.cc
	)

add_library(zziduo_object OBJECT ${ZZIDUO_SRC})