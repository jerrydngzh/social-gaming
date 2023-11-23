add_library(server
    STATIC
        server.cpp
)

target_include_directories(server
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(server
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

install(FILES "include/server.h"
    DESTINATION include
)
install(TARGETS server
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/server
)