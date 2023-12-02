add_executable(ServerPlatform
  ServerPlatform.cpp
)

set_target_properties(ServerPlatform
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(ServerPlatform
  networking
  ${CMAKE_THREAD_LIBS_INIT}
  # add other libraries here
  # Future: message-processors, game-engine, game {gameContainer, game}, server-processor
  
  core-game-engine-lib
  game-container-lib
  game-container-manager-lib
  server-manager-lib
  message-processors-lib
)

install(TARGETS ServerPlatform
  RUNTIME DESTINATION bin
)
