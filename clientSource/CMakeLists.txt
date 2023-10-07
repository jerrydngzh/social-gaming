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

# add_subdirectory(model)

# add_executable(client main.cpp) # this adds the source file to the project

# set_target_properties(client PROPERTIES
#     CXX_STANDARD 17
#     CXX_STANDARD_REQUIRED ON
# )

add_subdirectory(model/lib/Game)
add_subdirectory(model/lib/GameRoom)
add_subdirectory(model/lib/User)

add_executable(client main.cpp) # this adds the source file to the project

target_link_libraries(client gameroom)
target_link_libraries(client game)
target_link_libraries(client user)


set_target_properties(client PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")



# target_link_libraries(client  web-socket-networking)


# may need to use these commands 
# target_include_directories(gaming web-socket-networking/lib/networking/include)
# add_subdirectory(web-socket-networking/lib/networking/src)
# target_link_libraries(gaming single-threaded-web-socket-networking)


