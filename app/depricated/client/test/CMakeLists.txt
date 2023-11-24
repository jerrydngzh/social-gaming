if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_subdirectory(gtest)
endif()

add_executable(tests-client
    # Add new cpp files  that you want to add to testing
    dummyServerTests.cpp
    socialGameFileHandlerTests.cpp
    testClient.cpp
    testSocialGameFileHandler.cpp
    userTests.cpp
)

target_link_libraries(tests-client
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    dummyserver-lib
    socialgamefilehandler-lib
    user-lib
)

add_test(NAME tests-client
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-client
)
