// Purpose of the deserilizer is to read the game data from mikes data structure and initialize GameState with it
// Will basically have factory methods that return a ready GameState object
#pragma once

#include <fstream>
#include <iostream>
#include <sstream>

#include "gameState.h"
// #include staticDataStructure

extern "C" {
TSLanguage* tree_sitter_socialgaming();
}

class GameStateFactory {
    // THIS CURRENTLY STUBS ROCK PAPER SCISSORS!
   private:
    static std::string fileToString(const std::string& filepath) {
        std::ifstream file;
        file.open(filepath);

        if (!file.is_open()) {
            throw std::invalid_argument("Error opening file. Check if file path is correct");
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string fileContents = buffer.str();

        return fileContents;
    }

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

        // Rule Tree
        ts::Language language = tree_sitter_socialgaming();
        ts::Parser parser{language};
        ts::Tree* tree = new ts::Tree(parser.parseString(fileToString("test-game-files/rock-paper-scissors.game")));

        gameState.setRuleTree(tree);

        return gameState;
    }
};
