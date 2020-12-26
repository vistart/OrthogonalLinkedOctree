# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/vcpkg/scripts/buildsystems/vcpkg.cmake)
# set(CMAKE_TOOLCHAIN_FILE ~/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake)
project ("OrthogonalLinkedOctree" LANGUAGES CXX)
aux_source_directory(. DIR_SRCS)
include_directories("${PROJECT_SOURCE_DIR}/file_format/point_cloud_base_presentation")
include_directories("${PROJECT_SOURCE_DIR}/file_format/plyfile")
include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_list")
include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_octree")
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    message(
            STATUS "No CMAKE_BUILD_TYPE selected, defaulting to ${CMAKE_BUILD_TYPE}"
    )
endif()

add_compile_options(-D_DEBUG)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-D_DEBUG)
    message(
            STATUS "MARCO '-DEBUG' enabled."
    )
else()
    message(
            STATUS "MARCO '-DEBUG' disabled."
    )
endif()

# 包含子项目。
add_subdirectory ("file_format/point_cloud_base_presentation")
add_subdirectory ("file_format/plyfile")
add_subdirectory ("orthogonal_linked/orthogonal_linked_list")
add_subdirectory ("orthogonal_linked/orthogonal_linked_octree")
find_package(Boost)
if (Boost_FOUND)
    message("Boost FOUND " + ${Boost_VERSION})
    find_package(Boost COMPONENTS unit_test_framework)
    message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    message(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(WARNING "Boost NOT FOUND!")
endif()
find_package(pybind11)

set(SOURCES OrthogonalLinkedOctree.cpp)
set(CMAKE_CXX_STANDARD 17)
target_compile_features ("point_cloud_base_presentation" PUBLIC cxx_std_17)
target_compile_features ("plyfile" PUBLIC cxx_std_17)
target_compile_features ("orthogonal_linked_list" PUBLIC cxx_std_17)
target_compile_features ("orthogonal_linked_octree" PUBLIC cxx_std_17)

# 添加链接
add_executable(OrthogonalLinkedOctree ${SOURCES})
target_link_libraries(OrthogonalLinkedOctree orthogonal_linked_octree)
target_link_libraries(OrthogonalLinkedOctree orthogonal_linked_list)
target_link_libraries(OrthogonalLinkedOctree plyfile)
target_link_libraries(OrthogonalLinkedOctree point_cloud_base_presentation)
# target_link_libraries(OrthogonalLinkedOctree PRIVATE orthogonal_linked_list pybind11::lto pybind11::embed pybind11::module)
