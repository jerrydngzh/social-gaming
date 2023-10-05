#pragma once

#include <string_view>


class GameRoom;

class User {
public:
    bool getIsPlayer();
    bool getAudience();
    bool getOwner();
    User();

private:
    bool isPlayer;
    bool isAudience;
    bool isOwner;

    int gameRoomCode;
    std::string_view username;
};
