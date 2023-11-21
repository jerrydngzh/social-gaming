#include "gameContainer.h"
#include "../core-game-engine/lib/include/game.h"
#include "DTO.h"
#include "configuration.h"

GameContainer()
{
    Game gameInstance("filepath");
    // The configuration we are expectig is the one included in this file (Our code)
    // but currently it returns the configuration in game-container (Mike's code)
    Configuration *config = gameInstance.getConfiguration();
    std::vector<Configuration::Setting> settings = config->getSettings();
};

GameContainer::GameContainer() : ownerID(0), game(nullptr), gameInviteCode(0), playerList(){};

void GameContainer::getMsgFromGCManager(const GameContainerManagerDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        addPlayerToList(serverDTO.clientID);
    }
    else if (serverDTO.command == "INPUT")
    {
        //do something with player input, run game?
    }
}

GameContainerManagerDTO GameContainer::sendMsgToGCManager()
{
    GameContainerManagerDTO dto;

    return dto;
}
