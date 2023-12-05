// This will be in charge of knowing what rule we are currently at and what rules need to come next
// May contain the resume function, or maybe used by the resume function
#pragma once

#include <cpp-tree-sitter.h>

class RulesState {
   public:
    // Rules position
    ts::Tree* tree = nullptr;
    ts::Node currentNode = ts::Node(TSNode());
    ts::Node nextNode = ts::Node(TSNode());
    std::map<ts::Node*, Value*> instructionState;
    bool isParallel = false;

    // IO
    std::map<int, Value*> requests;

    RulesState(){};
    ~RulesState() {
        for (auto& [node, value] : instructionState) {
            delete value;
        }
        delete tree;
    }
};