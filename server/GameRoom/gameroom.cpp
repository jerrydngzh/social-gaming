#include "include/gameroom.h"
#include "../../Game/include/game.h"
#include <iostream>
#include <unordered_map>
#include <string_view>

GameRoom::GameRoom(int clientIdOfOwner1) : clientIdOfOwner(clientIdOfOwner1){}


std::unordered_map<int, std::string> GameRoom::runGame(std::unordered_map<int, std::string_view> clientInputs) {
    // loop through map
    for (const auto& pair : clientInputs) {
        int clientId = pair.first;
        std::string_view clientIdMessage = pair.second;
        switch (clientIdMessage)
        {
        // Example: "Join game room 5"
        case clientIdMessage.find("Join game room") != :
            int lastIndex = clientIdMessage.rfind(" ")
            
            break;
        
        default:
            break;
        }
    
    
    }
    // if else/switch statement to parse messages

    // call helper functions if needed to handle messages

}