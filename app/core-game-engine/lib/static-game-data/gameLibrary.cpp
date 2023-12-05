#include "gameLibrary.h"

GameLibrary::GameLibrary(const std::vector<Mapping> &data):
    contents(data),
    lookupMap({})
    {
      setLookups();
    }


GameLibrary::~GameLibrary() {}


Mapping GameLibrary::getMapping(int index) const {
  if(index >= 0 && index < contents.size()){
    return contents.at(index);
  }
  return {};
}// getMapping()


void GameLibrary::print() const {
    for(const Mapping& entry : contents){
      entry.print();
    }
}


std::variant<std::string, int, bool> GameLibrary::lookup(const std::string pathToFind) {
  auto entryIter = lookupMap.find(pathToFind);
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
    std::cout << "[ERROR] '" << pathToFind << "' NOT FOUND" << std::endl;
    return "notFound";
  }
}


void GameLibrary::setLookups() {
    for(Mapping& entry : contents) {
      std::pair<std::string, Mapping*> lookup = std::make_pair(entry.path, &entry);
      lookupMap.insert(lookup);
    }
}

