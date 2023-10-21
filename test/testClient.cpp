#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../client/lib/User/include/client.h"
#include <iostream>

using namespace testing;

class  ClientTests: public ::testing::Test {
public:
    Client clientAsh;
    void SetUp() override {
        clientAsh = Client("ash", true, false, true, 55);
    }

};
// Test is broken due to the inability to getInstruction. 
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

TEST_F(ClientTests, getClientNameTest) {
   ASSERT_EQ(true ,clientAsh.getClientName());
}

TEST_F(ClientTests, getConnectionStatusTest) {
   ASSERT_EQ(true ,clientAsh.getConnectionStatus());
}

TEST_F(ClientTests, createOrJoinGameTest){
    // we should enter 10
    std::string result = clientAsh.createOrJoinGame();
    std::cout << "Please enter 'amy' in the following line" << std::endl;
    ASSERT_EQ("amy" , result);

}
// TEST_F(ClientTests, testGetMessage){
//     // we should enter 10
//     clientAsh.getMessage("ola");
//     ASSERT_EQ(clientAsh.messageFromServer , "ola");

// }




