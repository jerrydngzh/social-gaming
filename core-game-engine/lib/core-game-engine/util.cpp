#include "util.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>


std::string parseGAMEFromFile(const std::string& filename){
    if(filename.find(GAME_FILE_EXTENSION) == std::string::npos){
        throw std::invalid_argument("File must be a GAME file");
    }

    std::ifstream file;
    file.open(filename);

    if(!file.is_open()){
        throw std::invalid_argument("Error opening file. Check if file path is correct");
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();

    return fileContents;
}