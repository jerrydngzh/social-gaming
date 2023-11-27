cmake_minimum_required(VERSION 3.24)

project(parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include(cmake/CPM.cmake)

# Downloads this wrapper library and tree-sitter.
# Makes them available via the `cpp-tree-sitter` CMake library target.
CPMAddPackage(
  NAME cpp-tree-sitter
  GIT_REPOSITORY https://github.com/nsumner/cpp-tree-sitter.git
  GIT_TAG v0.0.2
)

# Downloads a tree-sitter grammar from github and makes it available as a
# cmake library target.
add_grammar_from_repo(tree-sitter-json                 # Defines the library name for a grammar
  https://github.com/tree-sitter/tree-sitter-json.git  # Repository URL of a tree-sitter grammar
  0.19.0                                               # Version tag for the grammar
)

# Downloads a tree-sitter grammar from github and makes it available as a
# cmake library target.
add_grammar_from_repo(tree-sitter-sg                        # Defines the library name for a grammar
  https://github.com/nsumner/tree-sitter-socialgaming.git   # Repository URL of a tree-sitter grammar
  0.0.1                                                     # Version tag for the grammar
)

#********************************
#           LIBRARY
#********************************

# Configure the library to be tested
add_library(core-game-engine-lib)
target_sources(core-game-engine-lib
  PRIVATE
    rules.cpp
    treeParser.cpp
    util.cpp
    game.cpp
    interpreter.cpp
)
target_include_directories(core-game-engine-lib
  PUBLIC
    include/
)
target_compile_features(core-game-engine-lib PUBLIC cxx_std_20)
set_target_properties(core-game-engine-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)
target_link_libraries(core-game-engine-lib
  tree-sitter-json
  tree-sitter-sg
  cpp-tree-sitter
  static-game-data-lib
  game-state-lib
)

#include header
target_include_directories(core-game-engine-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
  ${tree-sitter-json_SOURCE_DIR} # This points to the include directory of tree-sitter-json
  ${tree-sitter-sg_SOURCE_DIR} # This points to the include directory of tree-sitter-json
)

add_subdirectory(game-state)
add_subdirectory(static-game-data)
