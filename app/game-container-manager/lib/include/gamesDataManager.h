/* TODO Code Review Interface General Notes
- Stringview vs String. This may not be correct, as Mike noted.
-  Documentation could have been more informative to clarify the design and context.
- There are not enough comments and documentation to understand the decision-making
process behind this design choice. Although the design is clear, more expressive
documentation could help reviewers and developers understand the code functionality
and context better.
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

// TODO: The DataObjects used to communicate between ServerProcessor and GameContainer is undefined.

/* GameContainer
    - What it's For:
    This Game Container is a Stub for the future Real GameContainer which will support playing an actual game.
    This stub helps to test that the serverProcessors can send data objects to, and recieve data objects from a Game Container.
    - How to Use: Whenever a GameContainer needs to be pinged, a Data Object should be passed into the game containers process(dataObject) parameter.
    The return value of the function should be a DataObject as well.
*/
class GameContainer
{
public:
    explicit GameContainer(int gameContainerID);
    [[nodiscard]] int getGameContainerID() const;

private:
    int gameContainerID;
};

// "manager" classes -- i.e. manages a collection of objects
// TODO: Consider making Clients Manager a component of GameContainerManager.
// TODO: More Comments are Needed

/* GameContainerManager
    - What it's For:
    The GameContainerManager handles the creation, deletion, modification, and message transfers of
    all GameContainers.
    - How to Use:
    The GameContainerManager should be constructed at a high level, and dependency injected into
    classes which wish to call its functionality.
*/
class GameContainerManager
{
public:
    GameContainerManager();

    int createGameContainer();

    bool doesGameContainerIDExist(int gameContainerID);

    std::string addPlayerToGame(int clientID, int gameContainerID);

    std::string giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data);

    // GameContainer getGameContainer(int gameContainerID);

private:
    int numberOfGameContainers = 0;
    std::vector<std::unique_ptr<GameContainer>> gameContainerVector;
    std::unordered_map<int, GameContainer *> gameContainerMap;
};

// TODO: maybe turn this into a map of users
//       maps have O(1) lookup time,
//       modification of particular user is O(1) as well
//       as we just lookup and then modify the specific field we want
//
// clientId -> user object
// as we pass down the clientId from the layer above, we can just use that to lookup the user

/* TODO: Be able to provide multiple way information.
    For example, ClientsManager should be able to answer "whats the owner of this game AND what game(s) does the player own."
    The same can be restated for players and games.
*/

/* TODO: ClientsManager Validation and consistent State Change
    The clientsManager should be responsible for maintaining a consistent and valid state at all times.
    If a user attempts to violate this, their actions should be stopped.
    For example, currently it is possible to set two owners of a game.
*/
// TODO: More Comments are Needed
/* TODO: Design is Too Specific
    which seems to make it hard to extend and add more functionalities later. For example,
    the design is just handling the roles of players and owners for now, and it may need to
    add more independent objects and methods for other roles such as audiences. What if
    an owner or an audience wants to become a player in the middle of gameplay? There
    aren’t any clear patterns that can support this functionality easily. It may be worth
    considering applying polymorphism in this design. Some other design patterns could
    also be a helpful addition to the refactoring process of this design because the current
    solution may make things difficult to refactor
*/

/* ClientsManager
    - What it's For:
    The ClientsManager keeps track of data about clients, and their relationships to game containers
    - How to Use:
    The ClientsManager should be constructed at a high level, and dependency injected into
    classes which wish to call its functionality.
*/
class ClientsManager
{
public:
    bool isClientPlayer(int clientID);

    void addPlayerToGame(int clientID, int clientGameCode);

    int getGameContainerIDofPlayer(int clientID);

    void setOwnerOfGameContainer(int clientID, int gameContainerID);

private:
    std::unordered_map<int, int> playerIDtoGameIDMap;
    std::unordered_map<int, int> ownerIDtoGameIDMap;
};