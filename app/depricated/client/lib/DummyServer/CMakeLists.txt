set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(dummyserver-lib)
target_sources(dummyserver-lib
  PRIVATE
    dummyserver.cpp
)
target_include_directories(dummyserver-lib
  PUBLIC
    include/
)
target_compile_features(dummyserver-lib PUBLIC cxx_std_20)
set_target_properties(dummyserver-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(dummyserver-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)