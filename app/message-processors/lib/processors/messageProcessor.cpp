#include "messageProcessor.h"
#include "json.hpp"
#include <iostream>
#include <sstream>

using namespace MessageProcessors;
using json = nlohmann::json;

const std::string JSON_CLIENT_ID_ACCESSOR = "clientId";
const std::string JSON_COMMAND_ACCESSOR = "command";
const std::string JSON_DATA_ACCESSOR = "data";

RequestMessageDTO MessageProcessor::processRequestMessageImpl(std::string_view message) {
    json jsonObj = json::parse(message);
    std::string command = jsonObj[JSON_COMMAND_ACCESSOR];
    
    // NOTE: we're passing down data as a string to be processed in the 
    //       layer below, as messageProcessor doesn't need to know the type of data
    std::string data = jsonObj[JSON_DATA_ACCESSOR];

    // NOTE: we leave knowledge of clientId to the layer above
    RequestMessageDTO requestMessageDTO{0, command, data};

    return requestMessageDTO;
}

std::string MessageProcessor::processResponseMessageImpl(const ResponseMessageDTO& message) {
    bool messageStatus = message.messageStatus;
    std::string_view messageResult = message.messageResult;
    std::string_view command = message.command;
    std::string_view commandData = message.commandData;

    std::stringstream jsonStream; 

    jsonStream << "{";
    jsonStream << "\"messageStatus\":" << std::boolalpha << messageStatus << ",";
    jsonStream << "\"messageResult\":\"" << messageResult << "\",";
    jsonStream << "\"command\":\"" << command << "\",";
    jsonStream << "\"commandData\":\"" << commandData << "\"";
    jsonStream << "}";

    std::string jsonString = jsonStream.str();
    return jsonString;
}

ClientResponseMessageDTO ClientMessageProcessor::processIncomingServerResponseMessageImpl(std::string_view message) {
    ClientResponseMessageDTO incomingDTO;
    try {
        json jsonObj = json::parse(message);

        bool messageStatus = jsonObj["messageStatus"];
        std::string messageResult = jsonObj["messageResult"];
        std::string command = jsonObj["command"];
        std::string commandData = jsonObj["commandData"];

        incomingDTO.messageStatus = messageStatus;
        incomingDTO.messageResult = messageResult;
        incomingDTO.command = command;
        incomingDTO.commandData = commandData;
    } catch (std::exception& e) {
        incomingDTO.messageStatus = false;
        incomingDTO.messageResult = "Error parsing incoming message";
    }
    return incomingDTO;
}

std::string ClientMessageProcessor::buildOutgoingClientMessageImpl(const ClientRequestMessageDTO& message) {
    std::string command = message.command;
    std::string data = message.data;

    std::stringstream jsonStream; 

    jsonStream << "{";
    jsonStream << "\"command\":\"" << command << "\",";
    jsonStream << "\"data\":\"" << data << "\"";
    jsonStream << "}";

    std::string jsonString = jsonStream.str();
    return jsonString;
}