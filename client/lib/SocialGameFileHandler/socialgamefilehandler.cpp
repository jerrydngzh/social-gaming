#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>

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

    // checks if the file exists at the path
    if(!std::filesystem::exists(filePath)) {
        std::cerr << "Error: File does not exist." << std::endl;
        return "";
    }

    std::ifstream fileStream(filePath);

    //opens the file and throws error if file cannot be opened
    if (!fileStream.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        return "";
    }

    //reads the file content using iterator
    std::istreambuf_iterator<char> begin(fileStream);
    std::istreambuf_iterator<char> end;

    std::string fileContent(begin, end);

    // closes the file
    fileStream.close();
    return fileContent;  
}
