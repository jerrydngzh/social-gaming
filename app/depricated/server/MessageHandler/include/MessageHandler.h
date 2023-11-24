#ifndef MESSAGE_HANDLERS_H
#define MESSAGE_HANDLERS_H

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <vector>
#include <tuple>

class MessageHandler {
public:
    virtual std::string getMessage(const int clientId) = 0;
    virtual void setClientMessage(const int clientId, std::string& message) = 0;
};

class ClientToServerMessageHandler : public MessageHandler {
private:
    std::unordered_map<int, std::string> clients;

public:
    ClientToServerMessageHandler();
    ~ClientToServerMessageHandler();
    void addClient(const int clientId);
    void removeClient(const int clientId);
    void setAllClientMessage(const std::string& message);
    std::vector<std::tuple<int, std::string>> getAllClientMessages() const;
    std::string allMessagesToString() const;
    std::vector<std::pair<int, std::string>> getClientSubsetMessages(const std::vector<int>& clientIds) const;
    void setClientSubsetMessages(const std::vector<int>& clientIds, const std::string& message);

    std::string getMessage(const int clientId) override;
    void setClientMessage(const int clientId, std::string& message) override;
};

class ServerToClientMessageHandler : public MessageHandler {
private:
    std::unordered_map<int, std::string> messagesToClients;

public:
    ServerToClientMessageHandler();
    ~ServerToClientMessageHandler();
    std::string getMessage(const int clientId) override;
    void setClientMessage(const int clientId, std::string& message) override;
};

#endif
