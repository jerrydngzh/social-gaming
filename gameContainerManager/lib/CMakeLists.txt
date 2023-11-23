add_library(serverProcessor_lib)

target_sources(serverProcessor_lib
  PRIVATE
    serverProcessor.cpp
)

target_include_directories(serverProcessor_lib
  PUBLIC
    include/
)
