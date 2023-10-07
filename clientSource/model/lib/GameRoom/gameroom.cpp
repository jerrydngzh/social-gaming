#include "include/gameroom.h"
#include "../../Game/include/game.h"

GameRoom::GameRoom() : gameCode(0) {}

GameRoom::GameRoom(int gameCode) : gameCode(gameCode) {}


/*

When a user connects to the game server, 
they may either join a game or create a new game amongst those served.
When a new game is created, it may be configured by the creating player,
who is designated as the “owner” of the game session and will have admin controls over the game.
The owner may configure the game and create it, after which they will receive an “invite code”.
*/ 

// Stub: Replace with actual implementation
void GameRoom::createGameRoom() {

}


