cmake_minimum_required(VERSION 3.20)
project(social-gaming)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# create output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(gtest)
add_subdirectory(client-platform)
add_subdirectory(core-game-engine)
add_subdirectory(game-container)
add_subdirectory(game-container-manager)
add_subdirectory(networking)
add_subdirectory(server-platform)
add_subdirectory(server-manager)


# copy game files to build directory
file(COPY game-files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
