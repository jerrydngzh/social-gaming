#pragma once

#include <string_view>


class GameRoom;

class User {
public:
    bool getIsPlayer();
    bool getIsAudience();
    bool getIsOwner();
    User(std::string_view username1,bool isPlayerr1,bool isAudience1,bool isOwner1,int code1);
    std::string_view getUserName();

private:
    bool isPlayer;
    bool isAudience;
    bool isOwner;

    int gameRoomCode;
    std::string_view username;
};
