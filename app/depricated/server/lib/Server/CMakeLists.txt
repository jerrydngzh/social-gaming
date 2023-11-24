set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(server-lib)
target_sources(server-lib
  PRIVATE
    server.cpp
)
target_include_directories(server-lib
  PUBLIC
    include/
)
target_compile_features(server-lib PUBLIC cxx_std_20)
set_target_properties(server-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(server-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)