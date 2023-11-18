#include "gameLibrary.h"

GameLibrary::GameLibrary(const std::vector<Mapping> &data):
    contents(data),
    lookupMap({})
    {
      setLookups();
    }


GameLibrary::~GameLibrary() {}


void GameLibrary::print() const {
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


void GameLibrary::setLookups() {
    for(Mapping& entry : contents) {
      std::pair<std::string, Mapping*> lookup = std::make_pair(entry.key, &entry);
      lookupMap.insert(lookup);
    }
}