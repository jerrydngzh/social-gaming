add_library(game STATIC game.cpp)

target_include_directories(game PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(FILES "include/game.h"
    DESTINATION include
)
install(TARGETS game
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/game
)