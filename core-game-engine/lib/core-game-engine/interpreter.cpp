#include <string>
#include <iostream>
#include <cpp-tree-sitter.h>
#include <map>

#include "interpreter.h"

extern "C" {
    TSLanguage* tree_sitter_socialgaming();
}

Interpreter::Interpreter(Game game, ts::Tree tree) :
    game(game),
    tree(tree)
{}

Interpreter::~Interpreter() {}

void Interpreter::recurse(ts::Node& n) {
    for (int i = 0; i < n.getNumChildren(); i++) {
        ts::Node child = n.getChild(i);

        const ts::Symbol type = child.getSymbol();

        auto actionIt = actions.find(type);

        if (actionIt != actions.end()) {
            Action* action = actionIt->second;
            action->execute(child);
        } else {
            // Handle other symbols as needed
            std::cout << "Unimplemented node type: " << child.getType() << std::endl;
        }
    }
}

const ts::Language Interpreter::language = tree_sitter_socialgaming();

ts::Symbol Interpreter::toSymbol(const std::string_view& symbolName) {
    return language.getSymbolForName(symbolName, true);
}

class Interpreter::TestAction : public Interpreter::Action {
public:
    void execute(ts::Node& node) override {
        recurse(node);
    }
};

// Create a mapping of symbols to actions objects
const std::map<ts::Symbol, Action*> Rules::actions = {
    {toSymbol("body"), new TestAction()}
    // Add more symbols and corresponding action objects
};