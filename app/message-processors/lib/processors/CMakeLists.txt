set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

add_library(message-processors-lib)

target_sources(message-processors-lib
  PRIVATE
    messageProcessor.cpp
)
target_include_directories(message-processors-lib
  PUBLIC
    include/
)
target_compile_features(message-processors-lib PUBLIC cxx_std_20)
set_target_properties(message-processors-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(message-processors-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


