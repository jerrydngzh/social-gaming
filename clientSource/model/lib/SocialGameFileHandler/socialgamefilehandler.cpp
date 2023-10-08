#include <iostream>
#include <memory>
#include <fstream>
#include "SocialGameFileHandler.h"

void sendFileToServer(const std::string file)
{
    std::cout << file << std::endl;
}

SocialGameFileHandler::SocialGameFileHandler()
{
    getGameConfigurationFile();
    sendFile();
}

void SocialGameFileHandler::getGameConfigurationFile()
{
    std::cout << "Enter the name of the game configuration file: ";
    std::cin >> fileName;
}

void SocialGameFileHandler::sendFile()
{
    std::ifstream configFile(fileName);
    if (!configFile.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
    }
    else
    {
        std::string line;
        while (std::getline(configFile, line))
        {
            sendFileToServer(line);
        }
        configFile.close();
    }
}
