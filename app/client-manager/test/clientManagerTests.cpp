#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ClientManager.h"

// matchCommandToIncomingCommand
TEST(ClientManagerTests, matchCommandToIncomingCommand)
{
    ClientManager clientManager{"localhost", "8080"};
    IncomingCommandType result = clientManager.matchCommandToIncomingCommand("QUIT");
    EXPECT_EQ(result, IncomingCommandType::QUIT);

    result = clientManager.matchCommandToIncomingCommand("MENU_SELECT");
    EXPECT_EQ(result, IncomingCommandType::MENU_SELECT);

    result = clientManager.matchCommandToIncomingCommand("INPUT");
    EXPECT_EQ(result, IncomingCommandType::INPUT);

    result = clientManager.matchCommandToIncomingCommand("INFO");
    EXPECT_EQ(result, IncomingCommandType::INFO);

    result = clientManager.matchCommandToIncomingCommand("GAME_END");
    EXPECT_EQ(result, IncomingCommandType::GAME_END);
    
    result = clientManager.matchCommandToIncomingCommand("SFASFD");
    EXPECT_EQ(result, IncomingCommandType::INVALID);
}

// isOutgoingCommandValid
TEST(ClientManagerTests, isOutgoingCommandValid_quit) 
{
    ClientManager clientManager{"localhost", "8080"};
    bool result = clientManager.isOutgoingCommmandValid("QUIT");
    EXPECT_EQ(true, result);
}

TEST(ClientManagerTests, isOutgoingCommandValid_exit) 
{
    ClientManager clientManager{"localhost", "8080"};
    bool result = clientManager.isOutgoingCommmandValid("EXIT");
    EXPECT_EQ(true, result);
}

TEST(ClientManagerTests, isOutgoingCommandValid_join) 
{
    ClientManager clientManager{"localhost", "8080"};
    bool result = clientManager.isOutgoingCommmandValid("JOIN");
    EXPECT_EQ(true, result);
}

TEST(ClientManagerTests, isOutgoingCommandValid_create) 
{
    ClientManager clientManager{"localhost", "8080"};
    bool result = clientManager.isOutgoingCommmandValid("CREATE");
    EXPECT_EQ(true, result);
}

TEST(ClientManagerTests, isOutgoingCommandValid_input) 
{
    ClientManager clientManager{"localhost", "8080"};
    bool result = clientManager.isOutgoingCommmandValid("INPUT");
    EXPECT_EQ(true, result);
}

TEST(ClientManagerTests, isOutgoingCommandValid_invalid) 
{
    ClientManager ClientManager{"localhost", "8080"};
    bool result = ClientManager.isOutgoingCommmandValid("sfsafs");
    EXPECT_EQ(false, result);
}

// textEntryHandler

// matchOutgoingCommandToCommand
TEST(ClientManagerTests, matchOutgoingCommandToRequest) 
{
    ClientManager clientManager{"localhost", "8080"};
    MessageProcessors::ClientRequestMessageDTO result = clientManager.matchOutgoingCommandToRequest("INPUT hello");
    EXPECT_EQ(result.command, "INPUT");
    EXPECT_EQ(result.data, "hello");
}

TEST(ClientManagerTests, matchOutgoingCommandToRequestEmptyData) 
{
    ClientManager clientManager{"localhost", "8080"};
    std::string command = "INPUT";
    MessageProcessors::ClientRequestMessageDTO result = clientManager.matchOutgoingCommandToRequest(command);
    EXPECT_EQ(result.command, command);
    EXPECT_EQ(result.data, "");
}

TEST(ClientManagerTests, matchOutgoingCommandToRequestEmptyCommand) 
{
    ClientManager clientManager{"localhost", "8080"};
    MessageProcessors::ClientRequestMessageDTO result = clientManager.matchOutgoingCommandToRequest(" hello");
    EXPECT_EQ(result.command, "INVALID");
    EXPECT_EQ(result.data, "hello");
}

TEST(ClientManagerTests, matchOutgoingCommandToRequestEmptyDataAndCommand) 
{
    ClientManager clientManager{"localhost", "8080"};
    MessageProcessors::ClientRequestMessageDTO result = clientManager.matchOutgoingCommandToRequest("");
    EXPECT_EQ(result.command, "INVALID");
    EXPECT_EQ(result.data, "");
}