#include <string>
#include <iostream>

#include "constants.h"
#include "mapping.h"

Constants::Constants(const std::vector<Mapping> &data):
    contents(data)
    {}


Constants::~Constants() {}


void Constants::print() const {
    for(const Mapping& entry : contents){
      std::cout << "Index   : " << entry.index << std::endl;
      std::cout << "Key     : " << entry.key << std::endl;
      std::cout << "Value   : " << entry.value << std::endl;
      std::cout << "Type    : " << entry.type << std::endl;
      std::cout << "Parent  : " << entry.parent << std::endl;
      std::cout << "Children: [";
      for(const int &child : entry.children){
        if(child != *entry.children.begin()){
            std::cout << ",";
        }
        std::cout << child;
      }
      std::cout << "]" << std::endl << std::endl;
    }
}