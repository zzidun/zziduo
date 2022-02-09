cmake_minimum_required(3.16.3)

project(hello)

set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_CPP_FLAGS "-fPIC")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(zziduo SHARED $<TARGET_OBJECT:zziduo_object>)