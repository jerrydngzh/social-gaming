// should replace game_state 
#include "gameContainer.h"

// Game Container Manager should pass in the server DTO right back in
GameContainer::GameContainer() : ownerID(0), game(nullptr), gameInviteCode(0), playerList(), serverDTO(serverDTO){
    game = std::make_unique<GameState>("../docs/rock-paper-scissors.game");


    // The configuration we are expecting is the one included in this file (Our code)
    // but currently it returns the configuration in game-container (Mike's code)
    // Configuration *config = game->getConfiguration();
    // settings = config->getSettings();

    // processing of the dto object
    ClientData clData = {serverDTO.data};
    InputOrJoin binaryEnum = JOIN;
    DTOtoGame dtoGame = {serverDTO.clientID,binaryEnum,clData};


    DtoFromGame dto = game->run(dtoGame);
};



void GameContainer::getMsgFromGCManager(const C2SDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        addPlayerToList(serverDTO.clientID);
        
    }
    else if (serverDTO.command == "INPUT")
    {
        
        // game->run();

    }
}

DTOtoGameContainerManager GameContainer::sendMsgToGCManager()
{
    DTOtoGameContainerManager dto;
    dto = {};
    // loop through each setting and send it one at a time, pause and rewait
    // to be discussed on Wed
    for (const auto& setting : settings) {

    }
    
}
