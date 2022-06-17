cmake_minimum_required(VERSION 3.22)
project(cmake_study)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
add_executable(cmake_study src/main.cpp)
