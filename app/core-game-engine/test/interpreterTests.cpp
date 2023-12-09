#include "deserializer.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "interpreter.h"

TEST(InterpreterTest, initialization) {
    GameState gs = GameStateFactory::createInitialGameState();
    Interpreter::run(&gs);
    EXPECT_TRUE(true);
}