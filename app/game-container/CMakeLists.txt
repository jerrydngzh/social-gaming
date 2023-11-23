cmake_minimum_required(VERSION 3.24)
project(game-container)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# create output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

add_subdirectory(lib)

include(CTest)
add_subdirectory(test)

