add_library(user STATIC user.cpp)

target_include_directories(user PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(FILES "include/user.h"
    DESTINATION include
)
install(TARGETS user
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/user
)