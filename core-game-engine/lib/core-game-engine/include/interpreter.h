#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <map>
#include <string_view>
#include "game.h"



// Handles the execution of a game
class Interpreter {
private:
    Game* game;
    const ts::Tree& tree;
    const static ts::Language language;

public:
    Interpreter(Game* game, const ts::Tree& tree);
    ~Interpreter();
    
    class Action {
    public:
        Game* game;
        virtual void execute(const ts::Node& node) = 0;
        virtual ~Action() {}
    };

    void run(const ts::Node& n);
    const static std::map<ts::Symbol, Action*> actions;
    static ts::Symbol toSymbol(const std::string_view& symbolName);
};