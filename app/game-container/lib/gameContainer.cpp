// should replace game_state 
#include "gameContainer.h"

// to stub out Interpreter for now
// we need a way to build the right 
Interpreter stubInterpeter{};

// Game Container Manager should pass in the server DTO right back in
// we need a static pointer to game container manager as well

void GameContainer::interpeterCommunication(GameState gs){
    this->lastResponse = stubInterpeter.run(gs);
}
void GameContainer::addPlayerToList(int clientID){
    playerList.push_back(clientID);
}

// may also want to get serverDTO in the constructor as well for processing purposes
GameContainer::GameContainer(int ownerId, int inviteCode, std::vector<int> playerList2 /*static game file*/, ClientsToServerDataObject serverDTO2) : ownerID(0), gameInviteCode(0), playerList(playerList2), serverDTO(serverDTO2) {
    // The configuration we are expecting is the one included in this file (Our code)
    // but currently it returns the configuration in game-container (Mike's code)
    // we want to move the two lines of ocde below to serverplatform
    // as thats where it should belong according to new design
    // Configuration *config = game->getConfiguration();
    // settings = config->getSettings();
    GameStateFactory gsFactory;
    game = gsFactory.createInitialGameState(/* passing in static data recieved in constructor*/);

    // we must initialize lastResponse with something, currently have initialized it with this
    lastResponse = {false,1,"command",myVariant,myTuple,mySetting,{}};


    // processing of the dto object
    ClientData clientData = {serverDTO.data};
    InputOrJoin binaryEnum = JOIN;
    DTOtoGame dtoGame = {serverDTO.clientID, binaryEnum, clientData};
    
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

DTOtoGameContainerManager GameContainer::proccessCommandAndGetNextRequest(const ClientsToServerDataObject& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        MemberState newUser{"temp", serverDTO.clientID};
        if(serverDTO.isPlayer){
            addPlayerToList(serverDTO.clientID);
            // game.addPlayer(&newUser);
        } else{
            // game.addAudience(&newUser);
        }
        
    }
    else if (serverDTO.command == "INPUT")
    {
        // we need to send it over to core game enginer after validation that the input is correct
        // Setting(std::string name, Kind kind) : name(name), kind(kind){};

        Setting::Kind kind = Setting::STRING;
        if(validateInput(serverDTO.command)){
            Setting newSetting{serverDTO.data, kind};
            // game.addSetting(&newSetting);
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
void GameContainer::addValidInput(std::string s){
    lastResponse.validInputs.push_back(s);
}

