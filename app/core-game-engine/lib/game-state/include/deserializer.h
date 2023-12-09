// Purpose of the deserilizer is to read the game data from mikes data structure and initialize GameState with it
// Will basically have factory methods that return a ready GameState object
#pragma once

#include "gameState.h"
// #include staticDataStructure

class GameStateFactory {
    // THIS CURRENTLY STUBS ROCK PAPER SCISSORS!
   public:
    static GameState createInitialGameState(/*StaticData d*/) {
        GameState gameState;

        // Constants
        StringValue* rockName = new StringValue("Rock");
        StringValue* paperName = new StringValue("Paper");
        StringValue* scissorsName = new StringValue("Scissors");

        MapValue* rock = new MapValue({{"name", rockName}, {"beats", scissorsName}});
        MapValue* paper = new MapValue({{"name", paperName}, {"beats", rockName}});
        MapValue* scissors = new MapValue({{"name", scissorsName}, {"beats", paperName}});

        ListValue* weapons = new ListValue("weapons", {rock, paper, scissors});

        gameState.addConstant(weapons);

        // Variables
        gameState.addVariable(new ListValue("winners", {}));

        // Per Player
        gameState.addPerPlayer(new IntegerValue("wins", 0));

                gameState.setGameFile("test-game-files/rock-paper-scissors.game");

        return gameState;
    }
};
