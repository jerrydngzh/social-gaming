#include <string>
#include <iostream>
#include <cpp-tree-sitter.h>
#include <map>

#include "rules.h"

extern "C" {
    TSLanguage* tree_sitter_socialgaming();
}

Rules::Rules(const ts::Node& node, const int numRounds) :
    node(node),
    currentRound(1),
    numRounds(numRounds)
{}

Rules::~Rules() {}


ts::Node Rules::getNode() const {
    return node;
}

std::string_view Rules::getContents(const std::string_view& gameFile) const {
    return node.getSourceRange(gameFile);
}


const int Rules::getCurrentRound() {
    return currentRound;
}

const int Rules::getNumRounds() {
    return numRounds;
}

void Rules::recurse(ts::Node n) {
    for (int i = 0; i < n.getNumChildren(); i++) {
        ts::Node child = n.getChild(i);

        const ts::Symbol type = child.getSymbol();
        auto actionIt = actions.find(type);
        if (actionIt != actions.end()) {
            Action* action = actionIt->second;
            action->execute(child);
        }
        else {
            // Handle other symbols as needed
            std::cout << "Unimplemented node type: " << child.getType() << std::endl;
        }
    }
}

const ts::Language Rules::language = tree_sitter_socialgaming();

ts::Symbol Rules::toSymbol(const std::string_view& symbolName) {
    return language.getSymbolForName(symbolName, true);
}

class TestAction : public Action {
public:
    void execute(ts::Node node) override {
        printf("HELLO FROM body\n");//Rules::recurse(node);
    }
};

// Create a mapping of symbols to actions objects
const std::map<ts::Symbol, Action*> Rules::actions = {
    {toSymbol("body"), new TestAction()}
    // Add more symbols and corresponding action objects
};