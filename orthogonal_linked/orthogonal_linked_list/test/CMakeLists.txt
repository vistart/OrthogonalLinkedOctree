set(CMAKE_CXX_STANDARD 17)
add_executable(OrthogonalLinkedOctreeTest Test.cpp)
target_link_libraries(OrthogonalLinkedOctreeTest PRIVATE Boost::boost Boost::unit_test_framework)