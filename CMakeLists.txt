cmake_minimum_required(VERSION 3.20)
project(hashtable)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(googletest-main)

include_directories(googletest-main/googletest/include/gtest)
set(SOURCE_FILES test.cpp hashtable.h hashtable.cpp)
add_executable(hashtable ${SOURCE_FILES})
target_link_libraries(hashtable gtest gtest_main)