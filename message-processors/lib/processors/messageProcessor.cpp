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
    // RequestMessageDTO requestMessageDTO;
    json jsonObj = json::parse(message);
    int clientId = jsonObj[JSON_CLIENT_ID_ACCESSOR];
    std::string command = jsonObj[JSON_COMMAND_ACCESSOR];
    
    // NOTE: we're passing down data as a string to be processed in the 
    //       layer below, as messageProcessor doesn't need to know the type of data
    std::string data = jsonObj[JSON_DATA_ACCESSOR];

    RequestMessageDTO requestMessageDTO{clientId, command, data};

    return requestMessageDTO;
}

std::string MessageProcessor::processResponseMessageImpl(const ResponseMessageDTO& message) {
    int clientId = message.clientId;
    bool messageStatus = message.messageStatus;
    std::string_view messageResult = message.messageResult;
    std::string_view command = message.command;
    std::string_view commandData = message.commandData;

    std::stringstream jsonStream; 

    jsonStream << "{";
    jsonStream << "\"clientId\":" << clientId << ",";
    jsonStream << "\"messageStatus\":" << std::boolalpha << messageStatus << ",";
    jsonStream << "\"messageResult\":\"" << messageResult << "\",";
    jsonStream << "\"command\":\"" << command << "\",";
    jsonStream << "\"commandData\":\"" << commandData << "\"";
    jsonStream << "}";

    std::string jsonString = jsonStream.str();
    return jsonString;
}