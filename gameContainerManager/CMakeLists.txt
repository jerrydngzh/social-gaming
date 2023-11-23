cmake_minimum_required(VERSION 3.20)
project(gameContainerManager) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the lib directory - must come before main or test. 
add_subdirectory(lib)

# Building Executable 
add_executable(main main.cpp)
target_link_libraries(main serverProcessor_lib)

# Building Test
add_subdirectory(test)