#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>


class DummyClient {
public:
    DummyClient();
    std::string createOrJoinGame();

    void process();
    void getMessage(std::string message);
    std::string setMessage();
    std::string getStringPrefix(const std::string& message);
    void runGameCode();
    void runGameInstruction();

    bool getConnectionStatus() const;

private:
    std::string messageForServer;
    std::string messageFromServer;

    bool connectionStatus = true;
};