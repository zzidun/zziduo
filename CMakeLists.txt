cmake_minimum_required(VERSION 3.16.3)

project(zziduo C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)


set(ZZIDUO_NAME	zziduo)
set(ZZIDUO_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(ZZIDUO_OUTPUT_DIRECTORY	${ZZIDUO_DIRECTORY}/output)
set(ZZIDUO_SOURCE_DIRECTORY ${ZZIDUO_DIRECTORY}/src)
set(ZZIDUO_HEADER_DIRECTORY ${ZZIDUO_DIRECTORY}/include)

set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)

add_compile_options(-fPIC -lpthread)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${ZZIDUO_SOURCE_DIRECTORY})

add_library(zziduo SHARED $<TARGET_OBJECTS:zziduo_object>)