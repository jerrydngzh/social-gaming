if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_subdirectory(gtest)
endif()

add_executable(tests-game-container-manager
    # Add new cpp files  that you want to add to testing
    gameContainerManagerTests.cpp
)

target_link_libraries(tests-game-container-manager
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    game-container-manager-lib
)

add_test(NAME tests-game-container-manager
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-game-container-manager
)
