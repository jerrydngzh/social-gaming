#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include "treeParser.h"
#include "util.h"
#include "configuration.h"

#include <cpp-tree-sitter.h>


extern "C" {
  TSLanguage* tree_sitter_socialgaming();
}

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Please provide a file to parse" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string fileContents = parseGAMEFromFile(filename);
    ts::Tree tree = parseTree(fileContents);
    ts::Node root = tree.getRootNode();
    ts::Node configuration = root.getNamedChild(0);

    for (int i = 0; i < configuration.getNumChildren(); i++) {
        std::cout << configuration.getNamedChild(i).getSymbol() << std::endl;
    }
}