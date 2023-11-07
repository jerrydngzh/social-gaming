#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "treeParser.h"
#include "rules.h"


TEST(Rules, POC_1) {
    EXPECT_TRUE(0 == 0);
}

TEST(Rules, POC_2) {
    EXPECT_FALSE(0 == 1);
}