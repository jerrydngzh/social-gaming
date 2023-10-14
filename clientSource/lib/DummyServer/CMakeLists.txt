add_library(dummyserver STATIC dummyserver.cpp)

target_include_directories(dummyserver PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(FILES "include/dummyserver.h"
    DESTINATION include
)
install(TARGETS dummyserver
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/dummyserver
)