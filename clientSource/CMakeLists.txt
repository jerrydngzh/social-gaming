cmake_minimum_required(VERSION 3.24)
project(client)

# this needs boost on your device so disabled for now
# include(FetchContent)

# FetchContent_Declare(
#     web-socket-networking
#     GIT_REPOSITORY https://github.com/nsumner/web-socket-networking.git
#     GIT_TAG 0.2
# )

# FetchContent_MakeAvailable(web-socket-networking)

add_subdirectory(model/lib/Game)
add_subdirectory(model/lib/GameRoom)
add_subdirectory(model/lib/User)
add_subdirectory(model/lib/SocialGameFileHandler)

add_executable(client main.cpp) # this adds the source file to the project

target_link_libraries(client gameroom)
target_link_libraries(client game)
target_link_libraries(client user)
target_link_libraries(client socialgamefilehandler)


set_target_properties(client PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")



