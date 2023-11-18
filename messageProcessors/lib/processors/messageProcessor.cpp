#include "messageProcessor.h"
#include "messageJson.h"

using namespace MessageProcessors;

IncomingMessageDTO MessageProcessor::processIncomingMessage(std::string_view message) {

    // TODO: serialize the message into a DTO

    IncomingMessageDTO incomingMessageDTO;
    incomingMessageDTO.clientId = "1";
    incomingMessageDTO.command = "command";
    incomingMessageDTO.data = "data";
    return incomingMessageDTO;
}

std::string MessageProcessor::processOutgoingMessage(OutgoingMessageDTO message) {
    // TODO: deserialize the message into a string
    auto clientId = message.clientId;
    auto messageStatus = message.messageStatus;
    auto messageResult = message.messageResult;
    auto command = message.command;
    auto commandData = message.commandData;
    buildMessageForClient(clientId, messageStatus, messageResult, command, commandData);
    return "message";
}