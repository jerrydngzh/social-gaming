#pragma once
#include "../../core-game-engine/lib/include/game.h"
#include "configuration.h"

class GameContainer
{
public:
    GameContainer();
    GameContainer(int ownerId, std::unique_ptr<Game> game, int inviteCode)
        : ownerID(ownerId), game(std::move(game)), gameInviteCode(inviteCode), playerList() {}

    void getMsgFromGCManager(const GameContainerManagerDTO& serverDTO);
    GameContainerManagerDTO sendMsgToGCManager();
    void addPlayerToList(int clientID);

    int getOwnerID() const { return ownerID; }
    int getGameInviteCode() const { return gameInviteCode; }
    const std::vector<int> &getPlayerList() const { return playerList; }

private:
    std::vector<Configuration::Setting> settings;
    int ownerID;
    std::unique_ptr<Game> game;
    int gameInviteCode;
    std::vector<player> playerList;
}