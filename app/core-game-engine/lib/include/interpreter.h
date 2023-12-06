#pragma once

#include <cpp-tree-sitter.h>

#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "gameState.h"

// Handles the execution of a game
class Interpreter {
   public:
    class Action {
       public:
        virtual void execute(const ts::Node& node) = 0;
        virtual ~Action() {}
    };

    const static ts::Language language;
    const static std::map<ts::Symbol, Action*> actions;
    static ts::Symbol toSymbol(const std::string_view& symbolName);
    Interpreter();
    ~Interpreter();

    void run(GameState gs);
};