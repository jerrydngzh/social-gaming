if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_subdirectory(gtest)
endif()

add_executable(tests-client-manager
    # Add new cpp files  that you want to add to testing
    clientManagerTests.cpp
)

target_link_libraries(tests-client-manager
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    client-manager-lib
    networking
    message-processors-lib
    # TODO: add all other libraries required for server-manager
)

add_test(NAME tests-client-manager
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-client-manager
)
