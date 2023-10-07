#include <cassert>
#include <cstdio>
#include <memory>
#include "treeParser.h"

extern "C" {
  TSLanguage* tree_sitter_socialgaming();
}

ts::Tree parseTree(const std::string& source){
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{ language };
    ts::Tree tree = parser.parseString(source);
    return tree;
}


