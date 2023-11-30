#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "messageProcessor.h"
#include "json.hpp"

using namespace MessageProcessors;

TEST(MessageProcessor, processIncomingMessage_ValidJsonFormat_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":1,\"command\":\"echo\",\"data\":\"hello world\"}";
    ResponseMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);

    EXPECT_EQ(requestMessageDTO.clientId, 1);
    EXPECT_EQ(requestMessageDTO.command, "echo");
    EXPECT_EQ(requestMessageDTO.data, "hello world");
}

TEST(MessageProcessor, processIncoming_EmptyMessage_test) {
    MessageProcessor messageProcessor; 
    std::string_view message = "";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

// ============= VALID =============
TEST(MessageProcessor, processIncoming_ValidClientId_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":333,\"command\":\"echo\",\"data\":\"hello world\"}";
    ResponseMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);
    EXPECT_EQ(requestMessageDTO.clientId, 333);
}

TEST(MessageProcessor, processIncoming_ValidCommand_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":333,\"command\":\"JOIN\",\"data\":\"hello world\"}";
    ResponseMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);
    EXPECT_EQ(requestMessageDTO.command, "JOIN");
}

TEST(MessageProcessor, processIncoming_ValidData_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":333,\"command\":\"echo\",\"data\":\"hello world\"}";
    ResponseMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);
    EXPECT_EQ(requestMessageDTO.data, "hello world");
}

// ============= INVALID =============
TEST(MessageProcessor, processIncoming_InvalidClientId_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":\"333\",\"command\":\"echo\",\"data\":\"hello world\"}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processIncoming_InvalidCommand_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":\"333\",\"command\":echo,\"data\":\"hello world\"}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processIncoming_InvalidData_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":333,\"command\":\"echo\",\"data\":true}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}


// ============= MISSING =============
TEST(MessageProcessor, processIncoming_MissingClientId_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":null,\"command\": \"echo\",\"data\":true}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processIncoming_MissingCommand_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":333,\"command\": null,\"data\":true}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processIncoming_MissingData_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":333,\"command\":\"echo\",\"data\":null}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processOutgoingMessage_ValidJsonFormat_test) {
    MessageProcessor messageProcessor;
    ResponseMessageDTO responseMessageDTO{1, true, "hello world", "echo", "hello world"};
    std::string responseMessage = messageProcessor.processOutgoingMessage(responseMessageDTO);
    std::string expectedResponseMessage = "{\"clientId\":1,\"messageStatus\":true,\"messageResult\":\"hello world\",\"command\":\"echo\",\"commandData\":\"hello world\"}";

    EXPECT_EQ(responseMessage, expectedResponseMessage);
}

TEST(MessageProcessor, processOutgoingMessage_EmptyMessage_test) {
    MessageProcessor messageProcessor;
    ResponseMessageDTO responseMessageDTO{0, NULL, "", "", ""};
    std::string expectedResponseMessage = "{\"clientId\":0,\"messageStatus\":false,\"messageResult\":\"\",\"command\":\"\",\"commandData\":\"\"}";
    std::string responseMessage = messageProcessor.processOutgoingMessage(responseMessageDTO);
    EXPECT_EQ(responseMessage, expectedResponseMessage);
}