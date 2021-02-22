aux_source_directory(. DIR_LIB_SRCS)
add_library (orthogonal_linked_octree_with_torch ${DIR_LIB_SRCS})
set(CMAKE_CXX_STANDARD 17)