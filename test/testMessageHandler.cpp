#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../server/MessageHandler/include/MessageHandler.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace testing;

class MessageHandlerTest : public::testing::Test {};

TEST_F(MessageHandlerTest, addNewClientTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    handler.addClient(id);
    std::string actualClientMsg = handler.getMessage(id);
    std::string expected = "";
    ASSERT_EQ(expected, actualClientMsg);
}

TEST_F(MessageHandlerTest, addNewClientInvalidTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    handler.addClient(id);
    std::string expectedFailStr = "Invalid argument: client already added";
    try{
        handler.addClient(id);
        FAIL();
    }catch(const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailStr);
    }
}

TEST_F(MessageHandlerTest, getMessageTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    handler.addClient(id);
    std::string expected = "hello there";
    handler.setClientMessage(id, expected);
    std::string actual = handler.getMessage(1);
    ASSERT_EQ(expected, actual);
}

TEST_F(MessageHandlerTest, getMessageFailTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    std::string expectedFailStr = "Invalid argument: cannot get message for unknown client";
    try{
        handler.getMessage(id);
        FAIL();
    }catch(const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailStr);
    }
}

TEST_F(MessageHandlerTest, setMessageTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    handler.addClient(id);
    std::string expected = "try setting";
    handler.setClientMessage(id, expected);
    std::string actual = handler.getMessage(1);
    ASSERT_EQ(expected, actual);
}

TEST_F(MessageHandlerTest, setMessageFailTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    std::string test = "try setting";
    std::string expectedFailStr = "Invalid argument: cannot set message for unknown client";
    try{
        handler.setClientMessage(id, test);
        FAIL();
    }catch(const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailStr);
    }
}

TEST_F(MessageHandlerTest, removeClientTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    handler.addClient(id);
    handler.removeClient(id);
    //Should fail after removal if we try retrieving the clients message.
    std::string expectedFailStr = "Invalid argument: cannot get message for unknown client";
    try{
        handler.getMessage(id);
        FAIL();
    }catch(const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailStr);
    }
}

TEST_F(MessageHandlerTest, removeClientFailTest) {
    ClientToServerMessageHandler handler{};
    int id = 1;
    std::string expectedFailStr = "Invalid argument: cannot remove client that wasn't added";
    try{
        handler.removeClient(id);
        FAIL();
    }catch(const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailStr);
    }
}

TEST_F(MessageHandlerTest, setAllClientMessageTest){
    ClientToServerMessageHandler handler{};
    int id1 = 1;
    int id2 = 2;

    handler.addClient(id1);
    handler.addClient(id2);

    std::string message = "Test Message for setAllClientMessageTest";
    handler.setAllClientMessage(message);

    std::string expectedMessage = message;
    std::string actual1 = handler.getMessage(id1);
    std::string actual2 = handler.getMessage(id2);

    ASSERT_EQ(expectedMessage, actual1);
    ASSERT_EQ(expectedMessage, actual2);

}

TEST_F(MessageHandlerTest, setAllClientMessageFailTest){
    ClientToServerMessageHandler handler{};
    int id = 1;

    std::string expectedFailString = "Invalid argument: cannot set message for unknown client";
    try {
        std::string message = "Test Message";
        handler.setAllClientMessage(message);
        FAIL();
    }
    catch (const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailString);
    }
}

TEST_F(MessageHandlerTest, getAllClientMessagesTest){
    ClientToServerMessageHandler handler{};
    int id1 = 1;
    int id2 = 2;

    handler.addClient(id1);
    handler.addClient(id2);

    std::string message = "Test Message for getAllClientMessagesTest";
    handler.setAllClientMessage(message);

    std::vector<std::tuple<int, std::string>> messages = handler.getAllClientMessages();
    
    for (const auto& msg : messages) {
        EXPECT_EQ(message, std::get<1>(msg));
    }
}

TEST_F(MessageHandlerTest, getAllClientMessagesFailTest){
    ClientToServerMessageHandler handler{};

    std::string expectedFailStr = "No clients added";
    try {
        std::vector<std::tuple<int, std::string>> messages = handler.getAllClientMessages();
        FAIL();
    }
    catch (const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailStr);
    }
}


TEST_F(MessageHandlerTest, allMessagesToStringTest) {
    ClientToServerMessageHandler handler{};
    int id1 = 1;
    int id2 = 2;

    handler.addClient(id1);
    handler.addClient(id2);

    std::string message = "Test Message";
    handler.setAllClientMessage(message);

    std::string expected = "Client: 1, Message: Test Message\nClient: 2, Message: Test Message\n";
    std::string actual = handler.allMessagesToString();

    ASSERT_EQ(expected, actual);
}

TEST_F(MessageHandlerTest, allMessagesToStringFailTest) {
    ClientToServerMessageHandler handler{};

    std::string expectedFailString = "No clients added";
    try {
        std::string result = handler.allMessagesToString();
        FAIL();
    }
    catch (const std::invalid_argument& err) {
        ASSERT_EQ(err.what(), expectedFailString);
    }
}
