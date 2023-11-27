if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_subdirectory(gtest)
endif()

add_executable(tests-server
    # Add new cpp files  that you want to add to testing
    testMessageHandler.cpp
)

target_link_libraries(tests-server
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    game-lib
    gameroom-lib
    server-lib
    message-handler-lib
)

add_test(NAME tests-server
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-server
)
