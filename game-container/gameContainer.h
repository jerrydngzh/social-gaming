#pragma once
#include "../../core-game-engine/lib/include/game.h"
#include "configuration.h"
#include <vector>

class GameContainer
{
public:
    GameContainer();
    GameContainer(int ownerId, std::unique_ptr<Game> game, int inviteCode)
        : ownerID(ownerId), game(std::move(game)), gameInviteCode(inviteCode), playerList() {}

    ForGameContainerManagerDTO GameContainerProcessor(const FromGameContainerManagerDTO & requestDTO);

    // int getOwnerID() const { return ownerID; }
    // int getGameInviteCode() const { return gameInviteCode; }
    // const std::vector<int> &getPlayerList() const { return playerList; }

private:
    void addPlayerToList(int clientID);
    // not sure about these functions anymore
    void getMsgFromGCManager(const GameContainerManagerDTO& serverDTO);
    GameContainerManagerDTO sendMsgToGCManager();

    std::vector<Configuration::Setting> settings; 
    int ownerID;
    std::unique_ptr<Game> game; 
    int gameInviteCode;
    //idk about the player type
    std::vector<int clientID> playerList;
    Configuration *config;
    
}