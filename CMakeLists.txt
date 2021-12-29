cmake_minimum_required(VERSION 3.20)

project(test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  HashTableTest
  test.cpp
  hashtable.cpp
  hashtable.h
)
target_link_libraries(
  HashTableTest
  gtest_main
)
