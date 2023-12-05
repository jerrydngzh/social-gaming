#pragma once
#include <iostream>

// this file is used to inherit the Mapping struct
// so we do not have have to include the treesitter header
// in our business logic
struct Mapping {
    int index;
    std::string path;
    std::string key;
    std::string value;
    int parent;
    std::vector<int> children;
    std::string type;

    Mapping& operator=(const Mapping &other) {
        if(this != &other) {
            index = other.index;
            key = other.key;
            value = other.value;
            parent = other.parent;
            children = other.children;
            type = other.type;
        }
        return *this;
    }

    bool operator==(const Mapping &other) {
        return (
            index == other.index &&
            key == other.key &&
            value == other.value && 
            parent == other.parent &&
            children == other.children &&
            type == other.type);
    }

    bool operator!=(const Mapping &other) {
        return (
            index != other.index ||
            key != other.key ||
            value != other.value ||
            parent != other.parent ||
            children != other.children ||
            type != other.type);
    }

    void print() const {
        std::cout << "Index   : " << index << std::endl;
        std::cout << "Path    : " << path << std::endl;
        std::cout << "Key     : " << key << std::endl;
        std::cout << "Value   : " << value << std::endl;
        std::cout << "Type    : " << type << std::endl;
        std::cout << "Parent  : " << parent << std::endl;
        std::cout << "Children: [";
        for(const int &child : children){
          if(child != *children.begin()){
              std::cout << ",";
          }
          std::cout << child;
        }
        std::cout << "]" << std::endl << std::endl;
    }
}; 
