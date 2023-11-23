cmake_minimum_required(VERSION 3.20)
project(social-gaming)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# create output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(gtest)
add_subdirectory(client)
add_subdirectory(client-server-communication)
add_subdirectory(core-game-engine)
add_subdirectory(game-container)
add_subdirectory(game-container-manager)
add_subdirectory(server)

add_executable(social-gaming
    main.cpp
)

target_link_libraries(social-gaming
  PRIVATE
    dummyserver-lib
    socialgamefilehandler-lib
    user-lib
    core-game-engine-lib
    game-container-lib
    game-container-manager-lib
    game-lib
    gameroom-lib
    server-lib
)

# copy game files to build directory
file(COPY game-files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
