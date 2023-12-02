// should replace game_state 
#include "gameContainer.h"

// to stub out Interpreter for now
// we need a way to build the right 
Interpeter stubInterpeter{};

// Game Container Manager should pass in the server DTO right back in
// we need a static pointer to game container manager as well

void GameContainer::interpeterCommunication(GameState gs){
    this->lastResponse = stubInterpeter.run(gs);
}
void GameContainer::addPlayerToList(int clientID){
    playerList.push_back(clientID);
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


bool GameContainer::validateInput(std::string input){
    // in the response we are getting from the game we have a vector of valid strings
    // simply check from that

    std::vector<std::string> vecOfValidInputs = this->lastResponse.validInputs;
    auto searchIndex = std::find(vecOfValidInputs.begin(), vecOfValidInputs.end(), input);
    if (searchIndex != vecOfValidInputs.end()){
        return true;
    }
    return false;

}

// helper function to convert DtoFromGame to DtoToContainerManager
DTOtoGameContainerManager GameContainer::GameContainerProcessor(const DtoFromGame& requestDTO){
    GameRequest request{requestDTO.command};
    DTOtoGameContainerManager newDto{requestDTO.clientID,playerList,requestDTO.setting,
                                     requestDTO.isParallel,requestDTO.value,requestDTO.range, request};
    return newDto;
}

DTOtoGameContainerManager GameContainer::proccessCommandAndGetNextRequest(const C2SDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        MemberState newUser{"temp", serverDTO.clientID};
        if(serverDTO.isPlayer){
            addPlayerToList(serverDTO.clientID);
            game.addPlayer(&newUser);
        } else{
            game.addAudience(&newUser);
        }
        
    }
    else if (serverDTO.command == "INPUT")
    {
        // we need to send it over to core game enginer after validation that the input is correct
        // Setting(std::string name, Kind kind) : name(name), kind(kind){};

        Setting::Kind kind = Setting::STRING;
        if(validateInput(serverDTO.command)){
            Setting newSetting{serverDTO.data, kind};
            game.addSetting(&newSetting);
        } 
        // If the input is not valid we need to send the response back to game container manager
        // Without running interpreter
        else {
            DTOtoGameContainerManager dto = GameContainerProcessor(lastResponse);
            return dto;
        }
    }
    interpeterCommunication(game);
    DTOtoGameContainerManager dto = GameContainerProcessor(lastResponse);
    return dto;
}


