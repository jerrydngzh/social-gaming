if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_subdirectory(gtest)
endif()

add_executable(tests-message-processors
    # Add new cpp files  that you want to add to testing
  messageProcessorsTests.cpp
)

target_link_libraries(tests-message-processors
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    message-processors-lib
)

add_test(NAME tests-message-processors
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-message-processors
)
