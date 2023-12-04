#include <variant>
#include <vector>
#include "configurationState.h"

enum MessageType{
    REQUEST_FOR_INPUT,
    OUTPUT_MESSAGE
};

enum InputOrJoin {
    INPUT,
    JOIN
};

struct ClientData {
    std::string data;
};

struct GameRequest {
    std::string request;
};

struct DtoFromGame {
    bool isParallel;
    int clientID;
    std::string command;
    std::variant<int, bool> value;
    std::tuple<int, int> range; // in the case of bool its one
    std::vector<Setting*> settings;
};

struct DTOtoGame {
    int clientID;
    InputOrJoin command;
    ClientData data;
};

// from andykamal:
// DTO:
// clientID: 3
// command: INPUT
// data: "rock"

// we translate =>

// to misha:
// DTO:
// clientID: 3
// command: 
// enum message: ROCK


// make some of these variables std::optional
struct DTOtoGameContainerManager {
    int clientId;
    std::vector<int> playerList;
    Setting setting; // on the client output(getPrompt())
    bool isParallel;
    std::variant<int, bool> value;
    std::tuple<int, int> range;
    GameRequest request; // general request such as players request, may not need this
};

struct ClientsToServerDataObject
{
    int clientID;
    std::string command;
    std::string data;
};