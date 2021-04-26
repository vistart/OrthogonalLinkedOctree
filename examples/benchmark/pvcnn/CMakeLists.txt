project(PVCNNBenchmark LANGUAGES CXX CUDA)
set(CMAKE_CXX_STANDARD 14)
# Sets the possible install locations
set(CUBLAS_HINTS
        ${CUDA_ROOT}
        $ENV{CUDA_ROOT}
        $ENV{CUDA_TOOLKIT_ROOT_DIR}
        )
set(CUBLAS_PATHS
        /usr
        /usr/local
        /usr/local/cuda
        )

# Finds the include directories
find_path(CUBLAS_INCLUDE_DIRS
        NAMES cublas_v2.h cuda.h
        HINTS ${CUBLAS_HINTS}
        PATH_SUFFIXES include inc include/x86_64 include/x64
        PATHS ${CUBLAS_PATHS}
        DOC "cuBLAS include header cublas_v2.h"
        )
mark_as_advanced(CUBLAS_INCLUDE_DIRS)

# Finds the libraries
find_library(CUDA_LIBRARIES
        NAMES cudart
        HINTS ${CUBLAS_HINTS}
        PATH_SUFFIXES lib lib64 lib/x86_64 lib/x64 lib/x86 lib/Win32 lib/import lib64/import
        PATHS ${CUBLAS_PATHS}
        DOC "CUDA library"
        )
mark_as_advanced(CUDA_LIBRARIES)
find_library(CUBLAS_LIBRARIES
        NAMES cublas
        HINTS ${CUBLAS_HINTS}
        PATH_SUFFIXES lib lib64 lib/x86_64 lib/x64 lib/x86 lib/Win32 lib/import lib64/import
        PATHS ${CUBLAS_PATHS}
        DOC "cuBLAS library"
        )
mark_as_advanced(CUBLAS_LIBRARIES)

# ==================================================================================================

# Notification messages
if(NOT CUBLAS_INCLUDE_DIRS)
    message(STATUS "Could NOT find 'cuBLAS.h', install CUDA/cuBLAS or set CUDA_ROOT")
endif()
if(NOT CUDA_LIBRARIES)
    message(STATUS "Could NOT find CUDA library, install it or set CUDA_ROOT")
endif()
if(NOT CUBLAS_LIBRARIES)
    message(STATUS "Could NOT find cuBLAS library, install it or set CUDA_ROOT")
endif()
include_directories(/usr/local/cuda/include)
include_directories(${PYTHON_INCLUDE_DIRS})
find_package(PythonLibs REQUIRED)
# Determines whether or not cuBLAS was found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cuBLAS DEFAULT_MSG CUBLAS_INCLUDE_DIRS CUDA_LIBRARIES CUBLAS_LIBRARIES)

#
set(CMAKE_NVCC_FLAGS "CMAKE_NVCC_FLAGS -std=c++14")
add_library(ball_query ball_query/ball_query.cu ball_query/ball_query.cuh ball_query/ball_query.cpp ball_query/ball_query.hpp)
target_compile_features(ball_query PUBLIC cxx_std_14)
add_library(voxelization voxelization/vox.cu voxelization/vox.cuh voxelization/vox.cpp voxelization/vox.hpp)
target_compile_features(voxelization PUBLIC cxx_std_14)
add_executable(PVCNNBenchmark PVCNNBenckmark.cpp)
target_link_libraries(PVCNNBenchmark ${PYTHON_LIBRARIES})
target_link_libraries(PVCNNBenchmark ${TORCH_LIBRARIES})
target_link_libraries(PVCNNBenchmark ball_query)
target_link_libraries(PVCNNBenchmark voxelization)

if (MSVC)
    message(STATUS "In Windows, We should copy all .dll files related torch manually to ensure the program ran successfully.")
        file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
        add_custom_command(TARGET PVCNNBenchmark
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${TORCH_DLLS}
                $<TARGET_FILE_DIR:PVCNNBenchmark>)
endif()