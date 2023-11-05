#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "treeParser.h"
#include "variables.h"


TEST(Variables, POC_1) {
    EXPECT_TRUE(0 == 0);
}

TEST(Variables, POC_2) {
    EXPECT_FALSE(0 == 1);
}