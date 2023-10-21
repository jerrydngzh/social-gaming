add_subdirectory(gtest)

add_executable(runAllTests
    testClient.cpp
    # Add new cpp files  thatt you want to add to testing
)

target_link_libraries(runAllTests
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    client/lib
    
)

add_test(NAME AllTests
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runAllTests
)

