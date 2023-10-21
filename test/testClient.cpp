#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../client/lib/User/include/client.h"

using namespace testing;

class  ClientTests: public ::testing::Test {
public:
    Client clientAsh;
    void SetUp() override {
        clientAsh = Client("ash", true, false, true, 55);
    }

};

TEST_F(ClientTests, runGameInstructionTest) {
   clientAsh.getMessage("game_instruction This is the game instruction!");
   
   ::testing::internal::CaptureStdout();
   clientAsh.runGameInstruction();
   std::string output = ::testing::internal::GetCapturedStdout();

   EXPECT_EQ(output, "This is the game instruction!");
}

TEST_F(ClientTests, getIsPlayerTest) {
   ASSERT_EQ(true ,clientAsh.getIsPlayer());
}
TEST_F(ClientTests, getIsAudienceTest) {
   ASSERT_EQ(false ,clientAsh.getIsAudience());
}
TEST_F(ClientTests, getIsOwnerTest) {
   ASSERT_EQ(true ,clientAsh.getIsOwner());
}




