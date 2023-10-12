#include <string>
#include <cpp-tree-sitter.h>

#include "rules.h"


Rules::Rules (const ts::Node& node, const int numRounds):
    node(node),
    currentRound(1),
    numRounds(numRounds)
    {}

Rules::~Rules () {}


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