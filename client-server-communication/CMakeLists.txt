cmake_minimum_required(VERSION 3.24)
project(server_main)

FetchContent_Declare(
    web-socket-networking
    GIT_REPOSITORY https://github.com/nsumner/web-socket-networking.git
    GIT_TAG 0.2
)
FetchContent_MakeAvailable(web-socket-networking)

add_executable(server_main server_main.cpp)

target_link_libraries(server_main server)

set_target_properties(server_main PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
