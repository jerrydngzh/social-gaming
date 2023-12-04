#pragma once

#include <cpp-tree-sitter.h>

#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "gameState.h"

// Handles the execution of a game
class Interpreter {
   private:
    // const Game* game;
    const ts::Tree& tree;
    const static ts::Language language;

   public:
    Interpreter(const ts::Tree& tree);
    ~Interpreter();

    class Action {
       public:
        virtual void execute(const ts::Node& node) = 0;
        virtual ~Action() {}
    };

    void run(const ts::Node& n);
    const static std::map<ts::Symbol, Action*> actions;
    static ts::Symbol toSymbol(const std::string_view& symbolName);
};