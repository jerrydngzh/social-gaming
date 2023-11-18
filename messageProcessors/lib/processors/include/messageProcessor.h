#include <string>

namespace MessageProcessors {

struct IncomingMessageDTO {
    std::string clientId;
    std::string command;
    std::string data;
};

struct OutgoingMessageDTO {
    std::string clientId;
    bool messageStatus;
    std::string messageResult;
    std::string command;
    std::string commandData;
};


// TODO: turn MessageProcessor class into a NVI with a MessageProcessorImpl
class MessageProcessor {
    public:
        static IncomingMessageDTO processIncomingMessage(std::string_view message);
        static std::string processOutgoingMessage(OutgoingMessageDTO message);
    private:
        static std::string buildMessageForClient(std::string clientId, bool messageStatus, std::string messageResult, std::string command, std::string commandData);
};


}

