cmake_minimum_required(VERSION 3.20)
project(social-gaming)

add_subdirectory(client)

include(CTest)
add_subdirectory(test)
