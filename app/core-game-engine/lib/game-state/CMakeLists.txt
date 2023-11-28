set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(game-state-lib)
target_sources(game-state-lib
  PRIVATE
    gameState.cpp
)
target_include_directories(game-state-lib
  PUBLIC
    include/
)
target_compile_features(game-state-lib PUBLIC cxx_std_20)
set_target_properties(game-state-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(game-state-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)