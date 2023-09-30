#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "message.h"

using namespace testing;
using namespace prompts;

TEST(messageTest, getMessage) {
    prompts::Message tester{42};

    EXPECT_TRUE(42 == tester.getNumber());
}