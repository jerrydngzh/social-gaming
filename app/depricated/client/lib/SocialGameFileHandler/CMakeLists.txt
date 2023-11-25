set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(socialgamefilehandler-lib)
target_sources(socialgamefilehandler-lib
  PRIVATE
    socialgamefilehandler.cpp
)
target_include_directories(socialgamefilehandler-lib
  PUBLIC
    include/
)
target_compile_features(socialgamefilehandler-lib PUBLIC cxx_std_20)
set_target_properties(socialgamefilehandler-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(socialgamefilehandler-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)