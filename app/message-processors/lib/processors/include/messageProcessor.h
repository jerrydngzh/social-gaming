#include <string>

namespace MessageProcessors {

// from the client
struct RequestMessageDTO {
    uintptr_t clientId;
    std::string command;
    std::string data;
};

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

}

