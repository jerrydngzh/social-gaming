cmake_minimum_required(VERSION 3.24)
project(client)

include(FetchContent)

FetchContent_Declare(
    web-socket-networking
    GIT_REPOSITORY https://github.com/nsumner/web-socket-networking.git
    GIT_TAG 0.2 
)

FetchContent_MakeAvailable(web-socket-networking)

add_executable(client main.cpp) # this adds the source file to the project
# target_link_libraries(client  web-socket-networking)

set_target_properties(client PROPERTIES
    CXX_STANDARD 21
    CXX_STANDARD_REQUIRED ON
)

# may need to use these commands 
# target_include_directories(gaming web-socket-networking/lib/networking/include)
# add_subdirectory(web-socket-networking/lib/networking/src)
# target_link_libraries(gaming single-threaded-web-socket-networking)


