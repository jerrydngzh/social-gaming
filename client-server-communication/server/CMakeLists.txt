add_executable(main_server
  main_server.cpp
)

set_target_properties(main_server
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(main_server
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS main_server
  RUNTIME DESTINATION bin
)

