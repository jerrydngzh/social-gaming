cmake_minimum_required(VERSION 3.24)
project(client)

add_subdirectory(lib/User)
add_subdirectory(lib/SocialGameFileHandler)
add_subdirectory(lib/DummyServer)

add_executable(client main.cpp) # this adds the source file to the project

target_link_libraries(client user)
target_link_libraries(client socialgamefilehandler)
target_link_libraries(client dummyserver)


set_target_properties(client PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
