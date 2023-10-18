#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <map>
#include <string_view>
#include "game.h"


// Handles the execution of a game
class Interpreter {
private:
    Game game;
    ts::Tree tree;
    const static ts::Language language;

public:
    Interpreter(Game game, ts::Tree tree);
    ~Interpreter();
    void recurse(ts::Node& n);
    const static std::map<ts::Symbol, Action*> actions;
    static ts::Symbol toSymbol(const std::string_view& symbolName);

    class Action {
    public:
        virtual void execute(ts::Node& node) = 0;
        virtual ~Action() {}
    };
};