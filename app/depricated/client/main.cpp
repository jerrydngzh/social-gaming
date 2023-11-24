#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

#include "client.h"
#include "dummyserver.h"

int main() {
    Client client;
    DummyServer server;

    std::string clientMailbox = "";
    std::string serverMailbox = "";

    bool clientConnected = true;

    while (clientConnected) {
        server.process();
        clientMailbox = server.setMessage(); // game_instruction user input rock paper or scissors.

        client.setMessage(clientMailbox);
        client.process();

        clientConnected = client.getConnectionStatus();
        if (clientConnected == false) {
            break;
        }

        serverMailbox = client.getMessage(); // join, create
        server.getMessage(serverMailbox);
    }

    return 0;
}