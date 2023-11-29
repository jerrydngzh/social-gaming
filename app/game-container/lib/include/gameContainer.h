#pragma once
// #include "../../core-game-engine/lib/include/game.h"
#include "gameState.h"
#include "configurationState.h"
#include "DTO.h"
#include <vector>
#include <memory>

class GameContainer
{
public:
    GameContainer();
    GameContainer(int ownerId, std::unique_ptr<GameState> game, int inviteCode)
        : ownerID(ownerId), game(std::move(game)), gameInviteCode(inviteCode), playerList() {}

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
    std::unique_ptr<GameState> game; 
    int gameInviteCode;
    std::vector<int> playerList; // list of clientIds
    Setting *config;
    DtoFromGame gameDTO;
    C2SDTO serverDTO;
};