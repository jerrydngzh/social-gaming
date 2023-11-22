#include <string>

namespace MessageProcessors {


// from the client
struct RequestMessageDTO {
    std::string clientId;
    std::string command;
    std::string data;
};

struct ResponseMessageDTO {
    int clientId;
    bool messageStatus; //could change to enums [SUCCESS, FAILED]
    std::string messageResult;
    std::string command;
    std::string commandData;
};

// TODO: turn MessageProcessor class into a NVI with a MessageProcessorImpl
class MessageProcessor {
    public:
        // TODO: change parameter to Message object during integration
        RequestMessageDTO MessageProcessor::processIncomingMessage(std::string_view message) {
            return processRequestMessageImpl(message);
        }
        
        // TODO: change return type to MessageResult object during integration
        std::string MessageProcessor::processOutgoingMessage(ResponseMessageDTO message) {
            return processResponseMessageImpl(message);
        }
    private:
        RequestMessageDTO processRequestMessageImpl(std::string_view message);
        std::string processResponseMessageImpl(const ResponseMessageDTO& message);
};

}

