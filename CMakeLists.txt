cmake_minimum_required (VERSION 2.6)
project (fastexp)

set(CMAKE_CXX_STANDARD 11)

message("Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/results)
configure_file(benchmark_template.cpp benchmark.cpp)
add_library(fast SHARED fastexp.cpp)
add_executable(benchmark benchmark.cpp)
