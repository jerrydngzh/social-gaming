add_library(messagehandler STATIC MessageHandler.cpp)

target_include_directories(messagehandler PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(FILES "include/messagehandler.h"
    DESTINATION include
)
install(TARGETS messagehandler
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/messagehandler
)