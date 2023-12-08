#include <string>

namespace MessageProcessors {

// from the client
struct RequestMessageDTO {
    uintptr_t clientId;
    std::string command;
    std::string data;
};

// TODO: refactor messageStatus name, to isRequestSuccessful
struct ResponseMessageDTO {
    uintptr_t clientId;
    bool messageStatus; //could change to enums [SUCCESS, FAILED]
    std::string messageResult;
    std::string command;
    std::string commandData;
};

class MessageProcessor {
    public:
        RequestMessageDTO processIncomingMessage(std::string_view message) {
            return processRequestMessageImpl(message);
        }
        
        std::string processOutgoingMessage(ResponseMessageDTO message) {
            return processResponseMessageImpl(message);
        }
    private:
        RequestMessageDTO processRequestMessageImpl(std::string_view message);
        std::string processResponseMessageImpl(const ResponseMessageDTO& message);
};


struct ClientRequestMessageDTO {
    std::string command;
    std::string data;
};

struct ClientResponseMessageDTO {
    bool messageStatus;
    std::string messageResult;
    std::string command;
    std::string commandData;
};

class ClientMessageProcessor {
    public:
        // TODO: unit test this
        ClientResponseMessageDTO processIncomingServerMessage(std::string_view message) {
            return processIncomingServerResponseMessageImpl(message);
        }
        
        // TODO: unit test this
        std::string buildOutgoingClientMessage(ClientRequestMessageDTO message) {
            return buildOutgoingClientMessageImpl(message);
        }
    private:
        ClientResponseMessageDTO processIncomingServerResponseMessageImpl(std::string_view message);
        std::string buildOutgoingClientMessageImpl(const ClientRequestMessageDTO& message);
};

}

