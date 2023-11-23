set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#********************************
#           LIBRARY
#********************************

# Configure the library
add_library(user-lib)
target_sources(user-lib
  PRIVATE
    client.cpp
)
target_include_directories(user-lib
  PUBLIC
    include/
)
target_compile_features(user-lib PUBLIC cxx_std_20)
set_target_properties(user-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

#include header
target_include_directories(user-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(user-lib
  PRIVATE
    socialgamefilehandler-lib
)
