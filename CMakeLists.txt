﻿# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.9)
project ("OrthogonalLinkedOctree" LANGUAGES CXX)
message(STATUS "The Operation System is ${CMAKE_HOST_SYSTEM_NAME}")
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    execute_process(COMMAND cat /etc/issue OUTPUT_VARIABLE issue_ov)
    message(STATUS ${issue_ov})
    # 工具链和 Python 可执行路径均为默认。请依据您自己的实际情况进行修改。
    # set(CMAKE_TOOLCHAIN_FILE ~/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake)
    set(PYTHON_EXECUTABLE /usr/bin/python3)
    # 只生成地址无关代码
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import torch; print(torch.utils.cmake_prefix_path, end='')" RESULT_VARIABLE TORCH_RV OUTPUT_VARIABLE TORCH_OV)
endif()
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Visual Studio 2019 would detect the vcpkg.cmake automatically.")
    # set(CMAKE_TOOLCHAIN_FILE C:/Users/vistart/source/repos/vcpkg/scripts/buildsystems/vcpkg.cmake)
    set(PYTHON_EXECUTABLE "C:/Program Files/Python39/python.exe")
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())" RESULT_VARIABLE PYTHON_RV OUTPUT_VARIABLE PYTHON_OV)
    set(PYTHON_INCLUDE_DIR ${PYTHON_OV})
    message(STATUS "PYTHON_INCLUDE_DIR: ${PYTHON_OV}")
    # 代码节数超过了默认上限，需要开启 bigobj。
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /bigobj")
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import torch; print(torch.utils.cmake_prefix_path, end='')" RESULT_VARIABLE TORCH_RV OUTPUT_VARIABLE TORCH_OV)
endif()

if (TORCH_RV EQUAL 0)
    add_compile_options(-D_TORCH)
    message(STATUS "MARCO '_TORCH' enabled.")
    include(${TORCH_OV}/Torch/TorchConfig.cmake)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
    message(STATUS "TORCH_INSTALL_PREFIX: ${TORCH_INSTALL_PREFIX}")
    include_directories(${TORCH_INSTALL_PREFIX}/include)
    include_directories(${TORCH_INSTALL_PREFIX}/include/torch/csrc/api/include)
else()
    message(STATUS "TORCH Disabled: ${TORCH_RV}")
endif()

aux_source_directory(. DIR_SRCS)
include_directories("${PROJECT_SOURCE_DIR}/file_format/point_cloud_base_presentation")
include_directories("${PROJECT_SOURCE_DIR}/file_format/plyfile")
include_directories("${PROJECT_SOURCE_DIR}/file_format/plyfile_for_python")
include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_list")
include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_octree")
if (TORCH_RV EQUAL 0)
    include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_octree_with_torch")
endif()
include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_octree_for_python")

# 引用所有测试项目代码仅在 Debug 模式下有效。
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_list_test")
    include_directories("${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_octree_test")
endif()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    message(
            STATUS "No CMAKE_BUILD_TYPE selected, defaulting to ${CMAKE_BUILD_TYPE}"
    )
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 添加“_DEBUG”宏，以便使某些语句仅在 Debug 模式下生效。
    add_compile_options(-D_DEBUG)
    message(
            STATUS "MARCO '_DEBUG' enabled."
    )
else()
    message(
            STATUS "MARCO '_DEBUG' disabled."
    )
endif()

# 包含子项目。
add_subdirectory ("file_format/point_cloud_base_presentation")
add_subdirectory ("file_format/plyfile")
add_subdirectory ("file_format/plyfile_for_python")
add_subdirectory ("orthogonal_linked/orthogonal_linked_list")
add_subdirectory ("orthogonal_linked/orthogonal_linked_octree")
if (TORCH_RV EQUAL 0)
    add_subdirectory ("orthogonal_linked/orthogonal_linked_octree_with_torch")
endif()
add_subdirectory ("orthogonal_linked/orthogonal_linked_octree_for_python")
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
pybind11_add_module(orthogonal_linked_octree_for_python SHARED
        "${PROJECT_SOURCE_DIR}/orthogonal_linked/orthogonal_linked_octree_for_python/orthogonal_linked_octree_for_python.cpp"
        )
target_link_libraries(orthogonal_linked_octree_for_python PRIVATE orthogonal_linked_octree orthogonal_linked_list plyfile point_cloud_base_presentation)
pybind11_add_module(plyfile_for_python SHARED
        "${PROJECT_SOURCE_DIR}/file_format/plyfile_for_python/plyfile_for_python.cpp"
        )
target_link_libraries(plyfile_for_python PRIVATE plyfile point_cloud_base_presentation)

set(SOURCES examples/OrthogonalLinkedOctreeWithTorch.cpp)
set(SOURCES examples/OrthogonalLinkedOctreeInPly.cpp)
set(CMAKE_CXX_STANDARD 17)

target_compile_features ("point_cloud_base_presentation" PUBLIC cxx_std_17)
target_compile_features ("plyfile" PUBLIC cxx_std_17)
target_compile_features ("plyfile_for_python" PUBLIC cxx_std_17)
target_compile_features ("orthogonal_linked_list" PUBLIC cxx_std_17)
target_compile_features ("orthogonal_linked_octree" PUBLIC cxx_std_17)
if (ENABLE_AVX2)
    if(MSVC)
        target_compile_options("orthogonal_linked_octree" INTERFACE /arch:AVX2)
    else()
        target_compile_options("orthogonal_linked_octree" INTERFACE -mavx2)
    endif()
    message(STATUS "ENABLE_AVX2: TRUE")
elseif(ENABLE_AVX512F)
    if(MSVC)
        target_compile_options("orthogonal_linked_octree" INTERFACE /arch:AVX512F)
    else()
        target_compile_options("orthogonal_linked_octree" INTERFACE -mavx512f)
    endif()
    message(STATUS "ENABLE_AVX512F: TRUE")
endif()
if (TORCH_RV EQUAL 0)
    target_compile_features ("orthogonal_linked_octree_with_torch" PUBLIC cxx_std_17)
endif()
target_compile_features ("orthogonal_linked_octree_for_python" PUBLIC cxx_std_17)

add_subdirectory ("examples")

# 所有测试项目仅在 Debug 模式下有效。
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory("orthogonal_linked/orthogonal_linked_list_test")
    add_subdirectory("orthogonal_linked/orthogonal_linked_octree_test")
endif()
