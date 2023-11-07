# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(socialgamefilehandler STATIC socialgamefilehandler.cpp)

target_include_directories(socialgamefilehandler PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(FILES "include/socialgamefilehandler.h"
    DESTINATION include
)
