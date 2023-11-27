if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_subdirectory(gtest)
endif()

add_executable(tests-server-manager
    # Add new cpp files  that you want to add to testing
    serverManagerTests.cpp
)

target_link_libraries(tests-server-manager
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    server-manager-lib
    networking
    # TODO: add all other libraries required for server-manager
)

add_test(NAME tests-server-manager
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-server-manager
)
