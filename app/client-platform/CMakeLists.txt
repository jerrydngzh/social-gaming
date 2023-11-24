add_executable(ClientPlatform
  ClientPlatform.cpp
  ChatWindow.cpp
)

set_target_properties(ClientPlatform
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(ClientPlatform
  networking
  ${CURSES_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS ClientPlatform
  RUNTIME DESTINATION bin
)

