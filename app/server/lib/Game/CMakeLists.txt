set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(game-lib)
target_sources(game-lib
  PRIVATE
    game.cpp
)
target_include_directories(game-lib
  PUBLIC
    include/
)
target_compile_features(game-lib PUBLIC cxx_std_20)
set_target_properties(game-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(game-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)