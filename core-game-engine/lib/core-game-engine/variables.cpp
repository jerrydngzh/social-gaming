
#include <string>
#include <cpp-tree-sitter.h>

#include "variables.h"

Variables::Variables(const std::vector<Mapping> &data):
    GameLibrary(data)
    {}

Variables::~Variables() {}