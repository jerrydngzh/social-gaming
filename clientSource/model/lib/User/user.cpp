#include "include/user.h"

bool User::getIsPlayer() {
    return isPlayer;
}

bool User::getIsAudience() {
    return isAudience;
}

bool User::getIsOwner() {
    return isAudience;
}

std::string_view User::getUserName(){
    return username;
}

User::User(std::string_view username1, bool isPlayer1, bool isAudience1, bool isOwner1, int code1)
    : username(username1), isPlayer(isPlayer1), isAudience(isAudience1), isOwner(isOwner1), gameRoomCode(code1) {
    
}

