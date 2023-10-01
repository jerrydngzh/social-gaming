#include <string_view>

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

    std::unique_ptr<GameRoom> gameRoomPtr;

    std::string_view username;
}
