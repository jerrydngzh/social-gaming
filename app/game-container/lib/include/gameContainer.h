#pragma once
#include "gameState.h"
#include "configurationState.h"
#include "DTO.h"
#include <vector>
#include <memory>
#include "deserializer.h"



class GameContainer
{
public:
    GameContainer(int ownerId,int inviteCode,std::vector<int> playerList2);

    DTOtoGameContainerManager GameContainerProcessor(const DtoFromGame& requestDTO);
    void interpeterCommunication(GameState gs);
    // DTOtoGameContainerManager sendMsgToGCManager();
    bool validateInput(std::string input);

    // this is the function gamecontainer manager should call from out side
    DTOtoGameContainerManager proccessCommandAndGetNextRequest(const C2SDTO& serverDTO);

    // helper functions that can be used for calling
    int getOwnerID() const { return ownerID; }
    int getGameInviteCode() const { return gameInviteCode; }
    const std::vector<int> &getPlayerList() const { return playerList; }

private:
    void addPlayerToList(int clientID);
    // not sure about these functions anymore
    std::vector<Setting> settings; 
    int ownerID;
    GameState game;
    int gameInviteCode;
    std::vector<int> playerList; // list of clientIds
    Setting *config;
    C2SDTO serverDTO;
    std::variant<int, bool> myVariant = static_cast<int>(42);
    std::tuple<int, int> myTuple = std::make_tuple(1, 2);
    Setting::Kind kind = Setting::STRING;
    Setting mySetting{"weapon", kind};
    DtoFromGame lastResponse = {false,1,"command",myVariant,myTuple,mySetting,{}};
    
};

// Stub class for interpreter as 
// we still need to integrate with real interpreter from core game engine
// and resolve dependency issues
class Interpreter {
public:
    DtoFromGame run(GameState gs){
        // will either return the apropriate value
        // or take in a repsonse dto which it will then proporgate by reference
        // so that we can read in stuff
        std::variant<int, bool> myVariant = static_cast<int>(42);
        std::tuple<int, int> myTuple = std::make_tuple(1, 2);
        Setting::Kind kind = Setting::STRING;
        Setting mySetting("weapon", kind);
        DtoFromGame myDto = {false,1,"command",myVariant,myTuple,mySetting,{}};
        return myDto;

    }
};