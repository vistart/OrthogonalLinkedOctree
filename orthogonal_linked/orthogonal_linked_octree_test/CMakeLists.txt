if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-D_DEBUG)
    message(
            STATUS "MARCO '_DEBUG' enabled."
    )
else()
    message(
            ERROR "OrthogonalLinkedOctreeTest is allowed to be built in Debug mode only."
    )
endif()
set(CMAKE_CXX_STANDARD 17)
include_directories("fixtures")
add_executable(OrthogonalLinkedOctreeTest Test.cpp)
target_link_libraries(OrthogonalLinkedOctreeTest PRIVATE Boost::boost Boost::unit_test_framework ${TORCH_LIBRARIES})