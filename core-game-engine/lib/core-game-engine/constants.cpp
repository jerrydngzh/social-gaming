
#include <string>
#include <cpp-tree-sitter.h>

#include "constants.h"

Constants::Constants(const ts::Node& node):
    node(node)
    {}

Constants::~Constants() {}

ts::Node Constants::getNode() const {
    return node;
}

std::string_view Constants::getContents(const std::string_view& gameFile) const {
    return node.getSourceRange(gameFile);
}