#include <iostream>
#include <memory>
#include <fstream>
#include "socialgamefilehandler.h"


SocialGameFileHandler::SocialGameFileHandler() {
    getGameConfigurationFile();
}

void SocialGameFileHandler::getGameConfigurationFile()
{
    std::cout << "Enter the name of the game configuration file: ";
    std::cin >> filePath;
}

std::string SocialGameFileHandler::getFile() {
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        return "";
    }

    std::istreambuf_iterator<char> begin(fileStream);
    std::istreambuf_iterator<char> end;

    std::string fileContent(begin, end);

    fileStream.close();
    return fileContent;  
}
