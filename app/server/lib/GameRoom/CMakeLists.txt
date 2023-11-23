set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(gameroom-lib)
target_sources(gameroom-lib
  PRIVATE
    gameroom.cpp
)
target_include_directories(gameroom-lib
  PUBLIC
    include/
)
target_compile_features(gameroom-lib PUBLIC cxx_std_20)
set_target_properties(gameroom-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(gameroom-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)