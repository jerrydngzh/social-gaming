add_subdirectory(gtest)

add_executable(testServerProcessor
  testServerProcessor.cpp
)

target_link_libraries(testServerProcessor
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    serverProcessor_lib
)
