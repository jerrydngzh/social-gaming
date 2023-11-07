#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "interpreter.h"


TEST(Interpreter, POC_1) {
    EXPECT_TRUE(0 == 0);
}

TEST(Interpreter, POC_2) {
    EXPECT_FALSE(0 == 1);
}