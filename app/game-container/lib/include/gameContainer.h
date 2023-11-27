#pragma once
// #include "../../core-game-engine/lib/include/game.h"
#include "game.h"
// #include "configuration.h"
#include "DTO.h"
#include <vector>

class GameContainer
{
public:
    GameContainer();
    GameContainer(int ownerId, std::unique_ptr<Game> game, int inviteCode)
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

    std::vector<Configuration::Setting> settings; 
    int ownerID;
    std::unique_ptr<Game> game; 
    int gameInviteCode;
    std::vector<int> playerList; // list of clientIds
    Configuration *config;
    DtoFromGame gameDTO;
    C2SDTO serverDTO;
};