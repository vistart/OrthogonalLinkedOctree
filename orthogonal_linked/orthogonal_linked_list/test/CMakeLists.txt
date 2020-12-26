set(CMAKE_CXX_STANDARD 17)
set(Boost_DEBUG ON)
find_package(Boost REQUIRED)
target_link_libraries(Test PRIVATE Boost::boost Boost::unit_test_framework)