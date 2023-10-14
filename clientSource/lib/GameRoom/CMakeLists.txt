add_library(gameroom STATIC gameroom.cpp)

target_include_directories(gameroom PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(FILES "include/gameroom.h"
    DESTINATION include
)
install(TARGETS gameroom
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/gameroom
)