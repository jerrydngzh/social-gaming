set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(static-game-data-lib)
target_sources(static-game-data-lib
  PRIVATE
    configuration.cpp
    constants.cpp
    gameLibrary.cpp
    perAudience.cpp
    perPlayer.cpp
    staticGameData.cpp
    variables.cpp
)
target_include_directories(static-game-data-lib
  PUBLIC
    include/
)
target_compile_features(static-game-data-lib PUBLIC cxx_std_20)
set_target_properties(static-game-data-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(static-game-data-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# link dependant libraries
target_link_libraries(static-game-data-lib
  core-game-engine-lib
)