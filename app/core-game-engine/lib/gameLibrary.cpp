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


std::variant<std::string, int, bool> GameLibrary::lookup(const std::string keyToFind) {
  auto entryIter = lookupMap.find(keyToFind);
  if(entryIter != lookupMap.end()){
    Mapping* entry = entryIter->second;
    std::string value = entry->value;
    std::string_view type = entry->type;

    if(type == "number") {
      return stoi(value);
    } else if(type == "boolean") {
      if(value == "true" || value == "True" || value == "1"){
        return true;
      } else {
        return false;
      }
    } else if(type == "quoted_string") {
      return value;
    }

    return value;
  } else{
    std::cout << "[ERROR] '" << keyToFind << "' NOT FOUND" << std::endl;
    return "notFound";
  }
}


void GameLibrary::setLookups() {
    for(Mapping& entry : contents) {
      std::pair<std::string, Mapping*> lookup = std::make_pair(entry.key, &entry);
      lookupMap.insert(lookup);
    }
}

