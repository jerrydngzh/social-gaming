cmake_minimum_required(VERSION 3.20)
project(social-gaming)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# create output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

add_subdirectory(gtest)
add_subdirectory(core-game-engine)
add_subdirectory(client)

add_executable(social-gaming
    main.cpp
)

target_link_libraries(social-gaming
  PRIVATE
    core-game-engine-lib
    dummyserver-lib
    socialgamefilehandler-lib
    user-lib
)
