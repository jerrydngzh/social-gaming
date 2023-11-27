#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "client.h"
#include <iostream>

using namespace testing;

class  ClientTests: public ::testing::Test {};

// Test is broken due to the inability to getInstruction. 
TEST_F(ClientTests, runGameInstructionTest) {
   Client clientAsh {"ash", true, false, true, 55};
   clientAsh.setMessage("game_instruction This is the game instruction!");
   // std::cout << "Type in: 'This is the game instruction!'" << std::endl;
   ::testing::internal::CaptureStdout();
   clientAsh.runGameInstruction();
   std::string output = ::testing::internal::GetCapturedStdout();

   ASSERT_EQ(output, "This is the game instruction!");
}

TEST_F(ClientTests, getIsPlayerTest) {
   Client clientAsh {"ash", true, false, true, 55};
   ASSERT_EQ(true ,clientAsh.getIsPlayer());
}
TEST_F(ClientTests, getIsAudienceTest) {
   Client clientAsh {"ash", true, false, true, 55};
   ASSERT_EQ(false ,clientAsh.getIsAudience());
}
TEST_F(ClientTests, getIsOwnerTest) {
    Client clientAsh {"ash", true, false, true, 55};
   ASSERT_EQ(true ,clientAsh.getIsOwner());
}

TEST_F(ClientTests, getClientNameTest) {
   Client clientAsh {"ash", true, false, true, 55};
   ASSERT_EQ("ash" ,clientAsh.getClientName());
}

TEST_F(ClientTests, getConnectionStatusTest) {
   Client clientAsh {"ash", true, false, true, 55};
   ASSERT_EQ(true ,clientAsh.getConnectionStatus());
}

TEST_F(ClientTests, createOrJoinGameTest){
     Client clientAsh {"ash", true, false, true, 55};
    // we should enter 10
    std::string result = clientAsh.createOrJoinGame();
    std::cout << "Please enter 'amy' in the following line" << std::endl;
    ASSERT_EQ("amy" , result);

}
TEST_F(ClientTests, testGetMessage){
   Client clientAsh {"ash", true, false, true, 55};
   ASSERT_EQ("",clientAsh.getMessage());
}




