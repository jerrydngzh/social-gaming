set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(server-manager-lib)
target_sources(server-manager-lib
  PRIVATE
    ServerManager.cpp
)
target_include_directories(server-manager-lib
  PUBLIC
    include/
)
target_compile_features(server-manager-lib PUBLIC cxx_std_20)
set_target_properties(server-manager-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

target_link_libraries(server-manager-lib
  PRIVATE
    core-game-engine-lib
    # game-container-lib
    game-container-manager-lib
    networking
    message-processors-lib
)

#include header
target_include_directories(server-manager-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)