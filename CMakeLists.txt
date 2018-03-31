cmake_minimum_required (VERSION 2.6)
project (fastexp)

set(CMAKE_CXX_STANDARD 11)

# Create directories to store results
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/results/float)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/results/double)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/plots)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python)

file(COPY python/benchmark.py DESTINATION python)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

configure_file(benchmark_template.cpp benchmark.cpp)
add_library(fast SHARED fastexp.cpp)
add_executable(benchmark benchmark.cpp)
