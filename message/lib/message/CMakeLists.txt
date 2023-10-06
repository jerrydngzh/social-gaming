# Configure the library to be tested
add_library(message)
target_sources(message
  PRIVATE
    message.cpp
)
target_include_directories(message
  PUBLIC
    include/
)
set_target_properties(message PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 17
)