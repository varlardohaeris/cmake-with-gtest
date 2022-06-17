cmake_minimum_required(VERSION 3.22)
project(cmake_study)

set(CMAKE_CXX_STANDARD 17)


enable_testing()
add_subdirectory(3rdparty/googletest)
include_directories(3rdparty/googletest/googletest/include)
include_directories(3rdparty/googletest/googlemock/include)

add_subdirectory(tests)
add_executable(cmake_study src/main.cpp)
