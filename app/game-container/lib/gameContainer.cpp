// should replace game_state 
#include "gameContainer.h"

// Game Container Manager should pass in the server DTO right back in
// we need a static pointer to game container manager as well

void GameContianer::interpeterCommunication(){

}

GameContainer::GameContainer() : ownerID(0), gameInviteCode(0), playerList(), serverDTO(serverDTO){
    // The configuration we are expecting is the one included in this file (Our code)
    // but currently it returns the configuration in game-container (Mike's code)
    // Configuration *config = game->getConfiguration();
    // settings = config->getSettings();
    GameState game = GameStateFactory::createInitialGameState(/* passing in static data recieved in constructor*/);

    // processing of the dto object
    ClientData clData = {serverDTO.data};
    InputOrJoin binaryEnum = JOIN;
    DTOtoGame dtoGame = {serverDTO.clientID,binaryEnum,clData};
    
    interpeterCommunication();

    
};




void GameContainer::getMsgFromGCManager(const C2SDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        
        MemberState newPlayer{"temp", serverDTO.clientID};
        addPlayerToList(serverDTO.clientID);
        game.addPlayer(&newPlayer);
        
        
    }
    else if (serverDTO.command == "INPUT")
    {
        
    }
}

GameContainer::askForSetting() {
    

}

DTOtoGameContainerManager GameContainer::sendMsgToGCManager()
{
    DTOtoGameContainerManager dto {};
    // dto = {};
    // loop through each setting and send it one at a time, pause and rewait
    // to be discussed on Wed
    for (const auto& setting : settings) {

    }
    
}
