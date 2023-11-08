add_executable(client_comm
  client_comm.cpp
  ChatWindow.cpp
)

set_target_properties(client_comm
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(client_comm
  networking
  ${CURSES_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS client_comm
  RUNTIME DESTINATION bin
)

