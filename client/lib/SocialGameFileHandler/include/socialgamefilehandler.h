#pragma once
#include <iostream>
#include <fstream>
#include <string>

// Prompts user to input the text file and "sends" it to the server as a string
// Example usage: 
// SocialGameFileHandler gameFile;
class SocialGameFileHandler
{
public:
    SocialGameFileHandler();
    
private:
    std::string fileName;
    
    void getGameConfigurationFile();
    void sendFile();
};