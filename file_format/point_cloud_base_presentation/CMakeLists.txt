cmake_minimum_required (VERSION 3.8)
project(point_cloud_base_presentation LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
aux_source_directory(. DIR_LIB_SRCS)
add_library (point_cloud_base_presentation ${DIR_LIB_SRCS})

set(CMAKE_CXX_STANDARD 17)