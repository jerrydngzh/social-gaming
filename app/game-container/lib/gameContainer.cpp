// should replace game_state 
#include "gameContainer.h"

// to stub out Interpreter for now
// we need a way to build the right 
Interpeter stubInterpeter{};

// Game Container Manager should pass in the server DTO right back in
// we need a static pointer to game container manager as well

void interpeterCommunication(GameState gs){
    stubInterpeter.run(gs);
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
    
    interpeterCommunication(game);

    
};


bool validateInput(std::string input){
    // in the response we are getting from the game we have a vector of valid strings
    // simply check from that


}

void GameContainer::getMsgFromGCManager(const C2SDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        if(serverDTO.isPlayer){
            MemberState newPlayer{"temp", serverDTO.clientID};
            addPlayerToList(serverDTO.clientID);
            game.addPlayer(&newPlayer);
        } else{
            MemberState newAudience{"temp", serverDTO.clientID};
            game.addAudience(&newAudience);
        }
    }
    else if (serverDTO.command == "INPUT")
    {
        // in the case of input
        // we need to send it over to core game enginer after validation that the input is correct
        // Setting(std::string name, Kind kind) : name(name), kind(kind){};

        Setting::Kind kind = Setting::STRING;
        if(validateInput(serverDTO.command)){
            Setting newSetting{serverDTO.data, kind};
            game.addSetting(&newSetting);
        }        
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
