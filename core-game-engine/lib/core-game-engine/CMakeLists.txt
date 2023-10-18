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


# Use the library in a main program.
add_executable(main)
target_sources(main
  PRIVATE
    configuration.cpp
    constants.cpp
    main.cpp
    perAudience.cpp
    perPlayer.cpp
    rules.cpp
    treeParser.cpp
    util.cpp
    variables.cpp
    game.cpp
)

target_link_libraries(main
  tree-sitter-json
  tree-sitter-sg
  cpp-tree-sitter
)

#include header
target_include_directories(main
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
  ${tree-sitter-json_SOURCE_DIR} # This points to the include directory of tree-sitter-json
  ${tree-sitter-sg_SOURCE_DIR} # This points to the include directory of tree-sitter-json
)

install(TARGETS main PUBLIC_HEADER
  DESTINATION ${PROJECT_BINARY_DIR}/bin
)