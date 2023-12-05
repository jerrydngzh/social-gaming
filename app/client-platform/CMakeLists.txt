add_executable(ClientPlatform
  ClientPlatform.cpp
)

set_target_properties(ClientPlatform
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

target_link_libraries(ClientPlatform
  networking
  message-processors-lib
  client-manager-lib
)

install(TARGETS ClientPlatform
  RUNTIME DESTINATION bin
)

