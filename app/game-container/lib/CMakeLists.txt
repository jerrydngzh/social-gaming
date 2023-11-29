set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include(cmake/CPM.cmake)

#********************************
#           LIBRARY
#********************************

# uncomment this during integration
CPMAddPackage(
  NAME cpp-tree-sitter
  GIT_REPOSITORY https://github.com/nsumner/cpp-tree-sitter.git
  GIT_TAG v0.0.2
)

# Configure the library
add_library(game-container-lib)
target_sources(game-container-lib
  PRIVATE
    gameContainer.cpp
)
target_include_directories(game-container-lib
  PUBLIC
    include/
)
target_compile_features(game-container-lib PUBLIC cxx_std_20)

# this may be needed during integration
target_link_libraries(game-container-lib
  cpp-tree-sitter
  # core-game-engine-lib
)

set_target_properties(game-container-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(game-container-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
