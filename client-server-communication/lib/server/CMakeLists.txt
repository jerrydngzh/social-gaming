add_library(server)

target_sources(server
    PRIVATE
        Server.cpp
        
)

target_include_directories(server 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
