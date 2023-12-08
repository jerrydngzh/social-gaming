#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "messageProcessor.h"
#include "json.hpp"

using namespace MessageProcessors;

TEST(MessageProcessor, processIncomingMessage_ValidJsonFormat_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\":\"echo\",\"data\":\"hello world\"}";
    RequestMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);

    EXPECT_EQ(requestMessageDTO.clientId, 0);
    EXPECT_EQ(requestMessageDTO.command, "echo");
    EXPECT_EQ(requestMessageDTO.data, "hello world");
}

TEST(MessageProcessor, processIncoming_EmptyMessage_test) {
    MessageProcessor messageProcessor; 
    std::string_view message = "";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

// ============= VALID =============
TEST(MessageProcessor, processIncoming_ValidCommand_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\":\"JOIN\",\"data\":\"hello world\"}";
    RequestMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);
    EXPECT_EQ(requestMessageDTO.command, "JOIN");
}

TEST(MessageProcessor, processIncoming_ValidData_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\":\"echo\",\"data\":\"hello world\"}";
    RequestMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);
    EXPECT_EQ(requestMessageDTO.data, "hello world");
}

// ============= INVALID =============
TEST(MessageProcessor, processIncoming_InvalidCommand_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\":echo,\"data\":\"hello world\"}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processIncoming_InvalidData_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\":\"echo\",\"data\":true}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}


// ============= MISSING =============
TEST(MessageProcessor, processIncoming_MissingCommand_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\": null,\"data\":true}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processIncoming_MissingData_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"command\":\"echo\",\"data\":null}";
    EXPECT_THROW(messageProcessor.processIncomingMessage(message), std::exception);
}

TEST(MessageProcessor, processOutgoingMessage_ValidJsonFormat_test) {
    MessageProcessor messageProcessor;
    ResponseMessageDTO responseMessageDTO{1, true, "hello world", "echo", "hello world"};
    std::string responseMessage = messageProcessor.processOutgoingMessage(responseMessageDTO);
    std::string expectedResponseMessage = "{\"messageStatus\":true,\"messageResult\":\"hello world\",\"command\":\"echo\",\"commandData\":\"hello world\"}";

    EXPECT_EQ(responseMessage, expectedResponseMessage);
}

TEST(MessageProcessor, processOutgoingMessage_EmptyMessage_test) {
    MessageProcessor messageProcessor;
    ResponseMessageDTO responseMessageDTO{0, NULL, "", "", ""};
    std::string expectedResponseMessage = "{\"messageStatus\":false,\"messageResult\":\"\",\"command\":\"\",\"commandData\":\"\"}";
    std::string responseMessage = messageProcessor.processOutgoingMessage(responseMessageDTO);
    EXPECT_EQ(responseMessage, expectedResponseMessage);
}

// Client Message Processors
TEST(MessageProcessor, processIncomingServerMessage_valid){
    ClientMessageProcessor clientMessageProcessor;
    std::string_view message = "{\"messageStatus\":true,\"messageResult\":\"hello world\",\"command\":\"echo\",\"commandData\":\"hello world\"}";
    ClientResponseMessageDTO clientResponseMessageDTO = clientMessageProcessor.processIncomingServerMessage(message);

    // messageStatus true
    EXPECT_TRUE(clientResponseMessageDTO.messageStatus);
    EXPECT_EQ(clientResponseMessageDTO.messageResult, "hello world");
    EXPECT_EQ(clientResponseMessageDTO.command, "echo");
    EXPECT_EQ(clientResponseMessageDTO.commandData, "hello world");

    // messageStatus false
    message = "{\"messageStatus\":false,\"messageResult\":\"hello world\",\"command\":\"echo\",\"commandData\":\"hello world\"}";
    clientResponseMessageDTO = clientMessageProcessor.processIncomingServerMessage(message);
    EXPECT_FALSE(clientResponseMessageDTO.messageStatus);
}

TEST(MessageProcessor, processIncomingServerMessage_invalid){
    ClientMessageProcessor clientMessageProcessor;
    std::string_view message = "";
    ClientResponseMessageDTO clientResponseMessageDTO = clientMessageProcessor.processIncomingServerMessage(message);

    EXPECT_EQ(clientResponseMessageDTO.messageStatus, false);
    EXPECT_EQ(clientResponseMessageDTO.messageResult, "Error parsing incoming message");
    EXPECT_EQ(clientResponseMessageDTO.command, "");
    EXPECT_EQ(clientResponseMessageDTO.commandData, "");
}

TEST(MessageProcessor, processIncomingServerMessage_empty){
    ClientMessageProcessor clientMessageProcessor;
    std::string_view message = "{\"messageStatus\":null,\"messageResult\":\"\",\"command\":\"\",\"commandData\":\"\"}";
    ClientResponseMessageDTO clientResponseMessageDTO = clientMessageProcessor.processIncomingServerMessage(message);

    EXPECT_EQ(clientResponseMessageDTO.messageStatus, false);
    EXPECT_EQ(clientResponseMessageDTO.messageResult, "Error parsing incoming message");
    EXPECT_EQ(clientResponseMessageDTO.command, "");
    EXPECT_EQ(clientResponseMessageDTO.commandData, "");
}

// buildOutgoingClientMessage
TEST(MessageProcessor, buildOutgoingClientMessage_valid){
    ClientMessageProcessor clientMessageProcessor;
    ClientRequestMessageDTO clientRequestMessageDTO{"INPUT", "hello world"};
    std::string outgoingMessage = clientMessageProcessor.buildOutgoingClientMessage(clientRequestMessageDTO);
    std::string expectedOutgoingMessage = "{\"command\":\"INPUT\",\"data\":\"hello world\"}";

    EXPECT_EQ(outgoingMessage, expectedOutgoingMessage);
}

TEST(MessageProcessor, buildOutgoingClientMessage_empty){
    ClientMessageProcessor clientMessageProcessor;
    ClientRequestMessageDTO clientRequestMessageDTO{"", ""};
    std::string outgoingMessage = clientMessageProcessor.buildOutgoingClientMessage(clientRequestMessageDTO);
    std::string expectedOutgoingMessage = "{\"command\":\"\",\"data\":\"\"}";

    EXPECT_EQ(outgoingMessage, expectedOutgoingMessage);
}

TEST(MessageProcessor, buildOutgoingClientMessage_invalid){
    ClientMessageProcessor clientMessageProcessor;
    ClientRequestMessageDTO clientRequestMessageDTO;
    std::string outgoingMessage = clientMessageProcessor.buildOutgoingClientMessage(clientRequestMessageDTO);
    std::string expectedOutgoingMessage = "{\"command\":\"\",\"data\":\"\"}";

    EXPECT_EQ(outgoingMessage, expectedOutgoingMessage);
}


