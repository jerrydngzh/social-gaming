#include "messageProcessor.h"
#include "messageJson.h"
#include <iostream>
#include <sstream>

using namespace MessageProcessors;

RequestMessageDTO MessageProcessor::processRequestMessageImpl(std::string_view message) {
    RequestMessageDTO requestMessageDTO;
    // TODO: find json library to searilize string to custom object
    // TODO: define the custom object structure
    return requestMessageDTO;
}

std::string MessageProcessor::processResponseMessageImpl(const ResponseMessageDTO& message) {
    int clientId = message.clientId;
    bool messageStatus = message.messageStatus;
    std::string_view messageResult = message.messageResult;
    std::string_vew command = message.command;
    std::string_view commandData = message.commandData;

    std::stringstream jsonStream; 

    jsonStream << "{";
    jsonStream << "\"clientId\":" << clientId << ",";
    jsonStream << "\"messageStatus\":" << std::boolalpha << messageStatus << ",";
    jsonStream << "\"messageResult\":\"" << messageResult << "\",";
    jsonStream << "\"command\":\"" << command << "\",";
    jsonStream << "\"commandData\":\"" << commandData << "\",";
    jsonStream << "}";

    std::string jsonString = jsonStream.str();
    return jsonString;
}