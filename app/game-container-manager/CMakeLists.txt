cmake_minimum_required(VERSION 3.24)
project(game-container-manager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# create output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(lib)

# Building Executable 
add_executable(main main.cpp)
target_link_libraries(main game-container-manager-lib)

# include(CTest)
# add_subdirectory(test)