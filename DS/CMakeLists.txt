cmake_minimum_required(VERSION 3.13.0)

project(DS CXX)

# Options. Turn on with 'cmake -Dmyvarname=ON'
option(test "Build all tests." ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)


include_directories(${CMAKE_SOURCE_DIR}/include/)

set(SOURCES
    src/main.cpp)

add_executable(ds ${SOURCES})

include(cmake/gtest.cmake)
target_link_libraries(ds PUBLIC GTest::gtest_main)
enable_testing()
include(GoogleTest)
gtest_discover_tests(ds)
