
#include <string>
#include <cpp-tree-sitter.h>

#include "perPlayer.h"

PerPlayer::PerPlayer(const ts::Node& node):
    node(node)
    {}

PerPlayer::~PerPlayer() {}

ts::Node PerPlayer::getNode() const {
    return node;
}

std::string_view PerPlayer::getContents(const std::string_view& gameFile) const {
    return node.getSourceRange(gameFile);
}