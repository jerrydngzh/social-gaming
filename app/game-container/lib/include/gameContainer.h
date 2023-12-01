#pragma once
// #include "../../core-game-engine/lib/include/game.h"
#include "gameState.h"
#include "configurationState.h"
#include "DTO.h"
#include <vector>
#include <memory>
#include "deserializer.h"



class GameContainer
{
public:
    GameContainer();
    GameContainer(int ownerId, GameState game, int inviteCode)
        : ownerID(ownerId), gameInviteCode(inviteCode), playerList() {}

    DTOtoGameContainerManager GameContainerProcessor(const DtoFromGame & requestDTO);

    // int getOwnerID() const { return ownerID; }
    // int getGameInviteCode() const { return gameInviteCode; }
    // const std::vector<int> &getPlayerList() const { return playerList; }

private:
    void addPlayerToList(int clientID);
    // not sure about these functions anymore
    void getMsgFromGCManager(const C2SDTO& serverDTO);
    DTOtoGameContainerManager sendMsgToGCManager();

    std::vector<Setting> settings; 
    int ownerID;
    GameState game;
    int gameInviteCode;
    std::vector<int> playerList; // list of clientIds
    Setting *config;
    DtoFromGame gameDTO;
    C2SDTO serverDTO;
};

// Stub class for interpreter as 
// we still need to integrate with real interpreter from core game engine
// and resolve dependencuy issues
class Interpeter {
public:
    DtoFromGame run(GameState gs){
        // will either return the apropriate value
        // or take in a repsonse dto which it will then proporgate by reference
        // so that we can read in stuff
        std::variant<int, bool> myVariant = static_cast<int>(42);
        std::tuple<int, int> myTuple = std::make_tuple(1, 2);
        DtoFromGame myDto = {false,1,"command",myVariant,myTuple,{},{}};
        return myDto;

    }
};