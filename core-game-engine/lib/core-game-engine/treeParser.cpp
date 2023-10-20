#include <cassert>
#include <cstdio>
#include <memory>
#include <iostream>

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

// class Extractor {
//     private:
//         Mapping temp;
//         std::string contents;

//         void recurse(const ts::Node &node, std::vector<Mapping> &data);
//     public:
//         Extractor(const std::string &fileContents);
//         ~Extractor();

//         std::vector<Mapping> format(const ts::Node &node);
// }

Extractor::Extractor(const std::string &fileContents):
  fileContents(fileContents),
  parent(0)
  {}

Extractor::~Extractor() {}


void Extractor::append(std::vector<Mapping> &data, const int &index, const std::string_view &key, const std::string_view &value, const int &parent, const std::string_view &type) {
  Mapping entry{};
  entry.index = index;
  entry.key = key;
  entry.value = value;
  entry.parent = parent;
  entry.type = type;

  if(data.size() > 0) {
    data.at(entry.parent).children.push_back(entry.index);    // set this entry as a child of it's parent
  }
  data.push_back(entry);                                    // add this entry to data
}


void Extractor::recurse(const ts::Node &node, std::vector<Mapping> &data) {
  std::string_view type = node.getType();
  std::string_view value = node.getSourceRange(fileContents);

  std::cout << std::endl << "Type: " << type << std::endl << "Value: " << value << std::endl;


  if(type == "identifier") {
      key = value;      // set the temporary key
    } else if (type == "integer" || type == "boolean" || type == "quoted_string") {
      append(data, data.size(), key, value, parent, type);
      key = "";
      value = "";
    } else if (type == "number_range") {
      // TODO
    } else if (type == "expression") {
      recurse(node.getChild(0), data);
    } else if (type == "expression_list") {
      int tempParent = parent;
      for(int i = 0; i < node.getNumChildren(); i++){
        if(node.getChild(i).getType() != ",") {
          int index = data.size();
          append(data, index, "", "", parent, type);
          parent = index;
          recurse(node.getChild(i), data);
        }
        parent = tempParent;
      }
    } else if (type == "list_literal") {
      int index = data.size();
      append(data, index, key, "", parent, type);
      parent = index;
      for(int i = 0; i < node.getNumChildren(); i++){
        recurse(node.getChild(i), data);
      }
    } else if (type == "map_entry") {
      for(int i = 0; i < node.getNumChildren(); i++){
        recurse(node.getChild(i), data);
      }
    } else if (type == "value_map") {
      for(int i = 0; i < node.getNumChildren(); i++){
        recurse(node.getChild(i), data);
      }
    // } else if (type == "qualified_identifier") {
    //   // TODO
    // } else if (type == "player_set") {
    //   // TODO
    // } else if (type == "body") {
    //   // TODO
    // } else if (type == "comment") {
    //   // TODO
    // }
    } else {
      if(type != "{" && type != "}" && type != "[" && type != "}") {
        std::cout << "[TODO] type: " << type << std::endl;
        for(int i = 0; i < node.getNumChildren(); i++) {
          recurse(node.getChild(i), data);
        }
      }
    }
}


std::vector<Mapping> Extractor::format(const ts::Node &node) {
  std::vector<Mapping> data;

  recurse(node, data);

  return data;
}
