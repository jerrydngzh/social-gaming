set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(client-manager-lib)
target_sources(client-manager-lib
  PRIVATE
    ClientManager.cpp
    ChatWindow.cpp
)
target_include_directories(client-manager-lib
  PUBLIC
    include/
)
target_compile_features(client-manager-lib PUBLIC cxx_std_20)
set_target_properties(client-manager-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(client-manager-lib
  PRIVATE
    networking
    message-processors-lib
    ${CURSES_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

#include header
target_include_directories(client-manager-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)