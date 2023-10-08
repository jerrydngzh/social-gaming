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

// int main(int argc, char *argv[]) {
//     if(argc < 2){
//         std::cout << "Please provide a file to parse" << std::endl;
//         return 1;
//     }

//     std::string filename = argv[1];
//     std::string fileContents = parseGAMEFromFile(filename);
//     std::cout << fileContents << std::endl;
//     return 0;
// }