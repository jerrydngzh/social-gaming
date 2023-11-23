add_subdirectory(gtest)

add_executable(tests-core-game-engine
    # Add new cpp files  that you want to add to testing
    configurationTests.cpp
    constantsTests.cpp
    gameTests.cpp
    gameLibraryTests.cpp
    interpreterTests.cpp
    perAudienceTests.cpp
    perPlayerTests.cpp
    rulesTests.cpp
    treeParserTests.cpp
    variablesTests.cpp
)

target_link_libraries(tests-core-game-engine
  PRIVATE
    GTest::gmock GTest::gtest GTest::gtest_main
    core-game-engine-test
)

add_test(NAME tests-core-game-engine
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests-core-game-engine
)
