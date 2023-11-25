#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "messageProcessor.h"
#include "json.hpp"

using namespace MessageProcessors;

TEST(MessageProcessor, processIncomingMessage_test) {
    MessageProcessor messageProcessor;
    std::string_view message = "{\"clientId\":1,\"command\":\"echo\",\"data\":\"hello world\"}";
    RequestMessageDTO requestMessageDTO = messageProcessor.processIncomingMessage(message);

    EXPECT_EQ(requestMessageDTO.clientId, 1);
    EXPECT_EQ(requestMessageDTO.command, "echo");
    EXPECT_EQ(requestMessageDTO.data, "hello world");
}

TEST(MessageProcessor, processOutgoingMessage_test) {
    MessageProcessor messageProcessor;
    ResponseMessageDTO responseMessageDTO{1, true, "hello world", "echo", "hello world"};
    std::string responseMessage = messageProcessor.processOutgoingMessage(responseMessageDTO);
    std::string expectedResponseMessage = "{\"clientId\":1,\"messageStatus\":true,\"messageResult\":\"hello world\",\"command\":\"echo\",\"commandData\":\"hello world\"}";

    EXPECT_EQ(responseMessage, expectedResponseMessage);
}


// TODO: add tests for the following test cases
/*
TESTS cases:
- processIncomingMessage
    - empty message
    - invalid json
    - valid json
        - clientId
            - missing
            - invalid type
            - valid
        - command
            - missing
            - invalid type
            - valid
        - data
            - missing
            - invalid type
            - valid

- processOutgoingMessage
    - empty message
    - invalid json
    - valid json
        - clientId
            - missing
            - invalid type
            - valid
        - messageStatus
            - missing
            - invalid type
            - valid
        - messageResult
            - missing
            - invalid type
            - valid
        - command
            - missing
            - invalid type
            - valid
        - commandData
            - missing
            - invalid type
            - valid
*/