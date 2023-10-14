#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

#include "user.h"
#include "dummyserver.h"

int main() {
    User client;
    DummyServer server;

    std::string clientMailbox = "";
    std::string serverMailbox = "";

    bool clientConnected = true;

    while (clientConnected) {
        server.process();
        clientMailbox = server.setMessage(); // game_instruction user input rock paper or scissors.

        client.getMessage(clientMailbox);
        client.process();

        clientConnected = client.getConnectionStatus();
        if (clientConnected == false) {
            break;
        }

        serverMailbox = client.setMessage(); // join, create
        server.getMessage(serverMailbox);
    }

    return 0;
}