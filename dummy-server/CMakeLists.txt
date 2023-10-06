cmake_minimum_required(VERSION 3.12)
project(RockPaperScissors)

set(CMAKE_CXX_STANDARD 11)


add_subdirectory(lib)

add_executable(RockPaperScissors main.cpp)
target_link_libraries(RockPaperScissors PRIVATE RPSGame)
