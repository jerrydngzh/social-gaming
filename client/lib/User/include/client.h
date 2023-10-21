#pragma once

#include <string_view>
#include <string>

class Client {
public:
    Client();
    Client(std::string_view Clientname1, bool isPlayerr1, bool isAudience1, bool isOwner1, int code1);

    bool getIsPlayer();
    bool getIsAudience();
    bool getIsOwner();
    std::string_view getClientName();
    std::string createOrJoinGame();

    void process();
    void getMessage(std::string message);
    std::string setMessage();
    std::string getStringPrefix(const std::string& message);
    void runGameCode();
    void runGameInstruction();

    bool getConnectionStatus() const;

private:
    bool isPlayer;
    bool isAudience;
    bool isOwner;

    int gameRoomCode;
    std::string_view Clientname; 
    std::string messageForServer;
    std::string messageFromServer;

    bool connectionStatus = true;
};
