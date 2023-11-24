set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(message-handler-lib)
target_sources(message-handler-lib
  PRIVATE
    MessageHandler.cpp
)
target_include_directories(message-handler-lib
  PUBLIC
    include/
)
target_compile_features(message-handler-lib PUBLIC cxx_std_20)
set_target_properties(message-handler-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(message-handler-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)