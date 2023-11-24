#include "../core-game-engine/lib/include/configuration.h"
#include <variant>

enum {
    REQUEST_FOR_INPUT,
    OUTPUT_MESSAGE
};

class DTO {
    bool isParallel;
    int clientID;
    std::string command;
    std::variant<int, bool> value;
    std::tuple<int, int> range; // in the case of bool its one
};