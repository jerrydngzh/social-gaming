add_library(client-lib)
target_sources(client-lib
    PRIVATE
        lib/game.cpp
        lib/gameroom.cpp
        lib/user.cpp
)

target_include_directories(client-lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)