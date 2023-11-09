// The purpose of this main.cpp is to ensure that the  Server Class compiles. 
// g++ -Wall -Werror main.cpp server.cpp -o my_server
// ./my_server 


// compile with cmake

// Whenever you make a change to Server, try running my_server to see if things compile. 


#include "server.h"
#include "gameroom.h"

int main() {
    // Server server;
    GameRoom gameRoom{1};
    gameRoom.addPlayer(2);

    std::unordered_map<int, std::string_view> clientCommands = {{5, "join game room"}};
    gameRoom.runGame(clientCommands);
    

    return 0;
}
