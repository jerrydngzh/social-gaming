#pragma once

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

//based off sample file in tree-sitter repo
const std::string GAME_FILE_EXTENSION = ".game";

std::string parseGAMEFromFile(const std::string& filename);