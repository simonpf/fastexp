cmake_minimum_required (VERSION 2.6)
project (fastexp)

set(CMAKE_CXX_STANDARD 11)

add_library(fast SHARED fastexp.cpp)
