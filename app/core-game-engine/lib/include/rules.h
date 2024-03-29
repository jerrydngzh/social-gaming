#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <map>


// Handles the rules section of the Game file

class Rules {
private:
    ts::Node node;
    int currentRound;
    int numRounds;

public:
    Rules(const ts::Node& node, const int numRounds);
    ~Rules();
    ts::Node getNode() const;
    std::string_view getContents(const std::string_view& gameFile) const;
    const int getCurrentRound();
    const int getNumRounds();
};