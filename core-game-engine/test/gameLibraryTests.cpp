#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameLibrary.h"


TEST(GameLibrary, POC_1) {
    EXPECT_TRUE(0 == 0);
}

TEST(GameLibrary, POC_2) {
    EXPECT_FALSE(0 == 1);
}