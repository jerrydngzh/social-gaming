add_library(gameroom 
    STATIC
        gameroom.cpp
)

target_include_directories(gameroom 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(gameroom
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

install(FILES "include/gameroom.h"
    DESTINATION include
)
install(TARGETS gameroom
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/gameroom
)