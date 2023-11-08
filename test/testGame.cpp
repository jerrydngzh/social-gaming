#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../server/lib/Game/include/game.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace testing;

class DummyGameTest : public::testing::Test {};

TEST_F(DummyGameTest, getTypeOfGame) {
    Game game;
    EXPECT_EQ(game.getTypeOfGame(), GameType::RockPaperScissors);
}

TEST_F(DummyGameTest, createJsonFile) {
    Game game;

    // create a dummy file and verify that .createJsonFile() can open it
    std::ofstream outfile ("dummy.json");
    outfile.close();

    std::ifstream dummyFile("dummy.json");
    EXPECT_EQ(game.createJsonFile().is_open(), dummyFile.is_open());

    remove("dummy.json");
}

TEST_F(DummyGameTest, getPlayerRange) {
    Game game;
    auto playerRange = std::make_tuple(0, 0);

    EXPECT_EQ(game.getPlayerRange(), playerRange);
}

// TODO: Add more tests / update stub tests when Game.cpp is fully implemented
