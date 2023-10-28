#include <string>
#include <iostream>
#include <cpp-tree-sitter.h>
#include <map>

#include "interpreter.h"

extern "C" {
    TSLanguage* tree_sitter_socialgaming();
}

Interpreter::Interpreter(const Game* game, const ts::Tree& tree):
    game(game),
    tree(tree)
{}


Interpreter::~Interpreter() {}

void Interpreter::run(const ts::Node& n) {
    const ts::Symbol type = n.getSymbol();

    auto actionIt = Interpreter::actions.find(type);

    if (actionIt != Interpreter::actions.end()) {
        Action* action = actionIt->second;
        action->execute(n);
    } else {
        // Handle other symbols as needed
        std::cout << "Unimplemented node type: " << n.getType()  << " (" << n.getSymbol() << ")" << std::endl;
    }
}

const ts::Language Interpreter::language = tree_sitter_socialgaming();

ts::Symbol Interpreter::toSymbol(const std::string_view& symbolName) {
    //std::cout << "symbolName: " << symbolName << " symbolEnum: " << language.getSymbolForName(symbolName, false) << std::endl;
    return language.getSymbolForName(symbolName, true);
}

class RecurseAction : public Interpreter::Action {
public:
    void execute(const ts::Node& node) override {
        for (int i = 0; i < node.getNumChildren(); i++) {
            ts::Node child = node.getChild(i);

            const ts::Symbol type = child.getSymbol();

            auto actionIt = Interpreter::actions.find(type);

            if (actionIt != Interpreter::actions.end()) {
                Action* action = actionIt->second;
                action->execute(child);
            } else {
                // Handle other symbols as needed
                std::cout << "Unimplemented node type: " << child.getType()  << " (" << child.getSymbol() << ")" << std::endl;
            }
        }
    }
};

class RuleAction : public Interpreter::Action {
public:
    void execute(const ts::Node& node) override {
        std::cout << "rule...\n";//node.getSExpr().get();
    }
};


class NoAction : public Interpreter::Action {
public:

    void execute(const ts::Node& node) override {
        //std::cout << node.getSExpr().get();
        return;
    }
};

// Create a mapping of symbols to actions objects
const std::map<ts::Symbol, Interpreter::Action*> Interpreter::actions = {
    {ts::Symbol(0), new NoAction()}, //No action by default
    {toSymbol("body"), new RecurseAction()},
    //{ts::Symbol(26), new NoAction()}, //Inner rules node (26)
    {ts::Symbol(98), new RecurseAction()}, //Outermost rules node (98)
    {toSymbol("rule"), new RuleAction()},
    // Add more symbols and corresponding action objects
};