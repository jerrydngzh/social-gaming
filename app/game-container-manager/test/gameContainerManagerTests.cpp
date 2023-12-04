#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ClientToServerDataObject.h" // c2sdto
#include "ServerToClientsDataObject.h" // s2cdto
#include "serverProcessors.h"
#include "gamesDataManager.h"

// Done! 
TEST(gameContainerManager, POC) {
    EXPECT_TRUE(true);
} // POC

// Done! 
TEST(DummyTestSuite, DummyTest) {
    // Arrange 
    int x = 1;
    int result = 0;

    // Act 
    result = x + 1;

    // Assert 
    EXPECT_EQ(result, 2);
};

// Done! 
TEST(ComponentTest, InitializationTest) {
    ASSERT_NO_THROW({
        GameContainerManager gameContainerManager;
        ClientsManager clientsManager;

        CreateProcessor createProcessor(gameContainerManager, clientsManager);
        JoinProcessor joinProcessor(gameContainerManager, clientsManager);
        InputProcessor inputProcessor(gameContainerManager, clientsManager);
        InvalidCommandProcessor invalidCommandProcessor;
    });
}

// Done! But can be improved
TEST(gameContainerManagerTest, CreateGameContainer){
    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    ASSERT_EQ(containerID, 0);
    // should also check that a game container is constructed? 
};

// Done! 
TEST(gameContainerManagerTest, DoesGameContainerIDExist_Success){
    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    ASSERT_TRUE(gameContainerManager.doesGameContainerExist(containerID));
};

// Done! 
TEST(GameContainerManagerTest, DoesGameContainerIDExist_Failure) {
    int containerID = 42;  
    GameContainerManager gameContainerManager;
    bool exists = gameContainerManager.doesGameContainerExist(containerID);
    ASSERT_FALSE(exists);
};

// Needs work 
// Maybe Not works and thats ok! 
TEST(GameContainerManagerTest, addPlayerToGame) { 
    GameContainerManager gameContainerManager;
    uintptr_t clientID = 1;
    int containerID = gameContainerManager.createGameContainer();
    std::string result = gameContainerManager.addPlayerToGame(clientID, containerID);

    // instead, check the gameContainer to see if the player is now in the game

    std::string expected = "client id " + std::to_string(clientID) + " added to game " + std::to_string(containerID) + "\n";
    ASSERT_EQ(result, expected);
};

// Done! 
TEST(GameContainerManagerTest, GiveGameContainerPlayerInput) {    
    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    uintptr_t clientID = 1;
    std::string inputData = "Some input data";
    std::string result = gameContainerManager.giveGameContainerPlayerInput(containerID, clientID, inputData);
    std::string expected = "gameContainer " + std::to_string(containerID) + " received player " + std::to_string(clientID) + " input: " + inputData + "\n";
    ASSERT_EQ(result, expected);   
};

// Done!
TEST(ClientsManagerTest, IsClientPlayer_Positive) {  
    uintptr_t clientID = 1;
    int clientGameCode = 0;
    ClientsManager clientsManager;

    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, clientGameCode); // here
    ASSERT_TRUE(addPlayerSuccess);
    
    bool isPlayer = clientsManager.isClientAlreadyPlayer(clientID);
    ASSERT_TRUE(isPlayer);
};

// Done!
TEST(ClientsManagerTest, IsClientPlayer_Negative) {
    uintptr_t clientID = 1;
    ClientsManager clientsManager;
    bool isPlayer = clientsManager.isClientAlreadyPlayer(clientID);
    ASSERT_FALSE(isPlayer);
};

// Done!
TEST(ClientsManagerTest, GetGameContainerIDofPlayer) {
    uintptr_t clientID = 1;
    int gameContainerID = 42; 
    ClientsManager clientsManager;
    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, gameContainerID); // refactored! may need to change response 
    ASSERT_TRUE(addPlayerSuccess);

    int retrievedGameContainerID = clientsManager.getGameContainerIDofPlayer(clientID);
    ASSERT_EQ(retrievedGameContainerID, gameContainerID);
};

// TODO: write a GetOwnerofGameContainer function, then complete test. 
//Maybe add a GetOwnerofGameContainer function
//Also, initialize ownerIDtoGameIDMap in ClientsManager constructor
// TEST(ClientsManagerTest, SetOwnerOfGameContainer) {
//     int clientID = 1;
//     int gameContainerID = 42; // A random game container ID
//     ClientsManager clientsManager;
//     clientsManager.setOwnerOfGameContainer(clientID, gameContainerID);
//     // ASSERT_TRUE(clientsManager.ownerIDtoGameIDMap.find(clientID) != clientsManager.ownerIDtoGameIDMap.end());
//     // ASSERT_EQ(clientsManager.ownerIDtoGameIDMap[clientID], gameContainerID);
// };

// Done!
TEST(CreateProcessor, processCreateCommand) {
    ClientToServerDataObject requestDTO = {1, "CREATE", "Some create data"};

    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    CreateProcessor createProcessor(gameContainerManager, clientsManager);
    ServerToClientsDataObject responseDTO = createProcessor.process(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "CREATE");
    ASSERT_EQ(responseDTO.data, "Response data from createGame");
};

// TODO no blockers
TEST(CreateProcessor, isCreateCommandValid) {
    // TODO
};

// Done!
TEST(CreateProcessor, createGame) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    CreateProcessor createProcessor(gameContainerManager, clientsManager);

    ClientToServerDataObject requestDTO = {1, "CREATE", "Some create data"};

    ServerToClientsDataObject responseDTO = createProcessor.createGame(requestDTO);  // Private Methods
  
    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "CREATE ROOM COMMAND SUCCESS");
    ASSERT_FALSE(responseDTO.data.empty());

};

// This can now be written 
TEST(CreateProcessor, invalidCreateCommandResponder) {
    
};


// DONE! 
TEST(JoinProcessor, processJoinCommand) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    ClientToServerDataObject requestDTO = {1, "JOIN", "123"};

    ServerToClientsDataObject responseDTO = joinProcessor.process(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "JOIN ROOM COMMAND SUCCESS");
    
    ASSERT_FALSE(responseDTO.data.empty()); 
};

// Done!
TEST(JoinProcessor, gameContainerExists) {

    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    int existingGameContainerID = gameContainerManager.createGameContainer();
    bool exists = joinProcessor.gameContainerExists(existingGameContainerID);
    ASSERT_TRUE(exists);
};

// Done
TEST(JoinProcessor, isClientAlreadyPlayer) {
    
    ClientsManager clientsManager;
    GameContainerManager gameContainerManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    uintptr_t clientID = 1;
    int gameContainerID = 456; 
    // clientsManager.addPlayerToGame(clientID, gameContainerID);

    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, gameContainerID);
    ASSERT_TRUE(addPlayerSuccess);

    bool alreadyPlayer = joinProcessor.isClientAlreadyPlayer(clientID);
    ASSERT_TRUE(alreadyPlayer);
};

TEST(JoinProcessor, isJoinCommandValid) {
    
};

// DONE!
TEST(JoinProcessor, joinGame) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    
    ClientToServerDataObject requestDTO = {1, "JOIN", "123"};
    
    ServerToClientsDataObject responseDTO = joinProcessor.process(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "JOIN ROOM COMMAND SUCCESS");
    
    ASSERT_FALSE(responseDTO.data.empty()); 
};

// Done!
TEST(JoinProcessor, invalidJoinCommandResponder_ClientAlreadyPlayer) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    int existingGameContainerID = gameContainerManager.createGameContainer();
    uintptr_t clientID = 1;

    // Add the player to the game (simulate a client already being a player)
    // clientsManager.addPlayerToGame(clientID, existingGameContainerID);
    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, existingGameContainerID);
    ASSERT_TRUE(addPlayerSuccess);
    

    ClientToServerDataObject requestDTO = {clientID, "JOIN", std::to_string(existingGameContainerID)};
 
     // ServerToClientsDataObject responseDTO;
    ServerToClientsDataObject responseDTO = joinProcessor.invalidJoinCommandResponder(requestDTO); // private method

    ASSERT_EQ(responseDTO.command, "INVALID JOIN COMMAND");
    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_TRUE(responseDTO.data.find("Client " + std::to_string(requestDTO.clientID) + " is already a Player.") != std::string::npos);
    ASSERT_FALSE(responseDTO.data.empty()); // There should be an error message
};

//Done!
TEST(InputProcessor, processInputCommand) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
    
    int existingGameContainerID = gameContainerManager.createGameContainer();
    uintptr_t clientID = 1;

    // clientsManager.addPlayerToGame(clientID, existingGameContainerID);

    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, existingGameContainerID);
    ASSERT_TRUE(addPlayerSuccess);

    ClientToServerDataObject requestDTO = {clientID, "INPUT", "Some input data"};

    ServerToClientsDataObject responseDTO = inputProcessor.process(requestDTO); 

    ASSERT_EQ(responseDTO.command, "VALID INPUT COMMAND");
    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_TRUE(responseDTO.data.find("Game Container " + std::to_string(existingGameContainerID) +
                                      " received player " + std::to_string(requestDTO.clientID) +
                                      " input: " + requestDTO.data) != std::string::npos);
};

// Done!
TEST(InputProcessor, isClientPlayer) {
    
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
        
    uintptr_t clientID = 1;
    int gameContainerID = gameContainerManager.createGameContainer();

    // clientsManager.addPlayerToGame(clientID, gameContainerID);

    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, gameContainerID); // here
    ASSERT_TRUE(addPlayerSuccess);

    bool isPlayer = inputProcessor.isClientPlayer(clientID);

    ASSERT_TRUE(isPlayer);
};

// Done!
TEST(InputProcessor, isInputCommandValid) {
       
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
        
    uintptr_t clientID = 1;
    int gameContainerID = gameContainerManager.createGameContainer();

    // clientsManager.addPlayerToGame(clientID, gameContainerID);

    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, gameContainerID); // here
    ASSERT_TRUE(addPlayerSuccess);

    ClientToServerDataObject requestDTO = {clientID, "INPUT", "Some input data"};

    bool isValid = inputProcessor.isInputCommandValid(requestDTO);

    ASSERT_TRUE(isValid);
};

// Done!
TEST(InputProcessor, invalidInputCommandResponder) {

    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
 
    uintptr_t clientID = 1;
    int gameContainerID = gameContainerManager.createGameContainer();

    // clientsManager.addPlayerToGame(clientID, gameContainerID);

    bool addPlayerSuccess = clientsManager.addPlayerToGame(clientID, gameContainerID); // here
    ASSERT_TRUE(addPlayerSuccess);

    ClientToServerDataObject requestDTO = {clientID, "INVALID_INPUT", "Some invalid input data"};
    ServerToClientsDataObject responseDTO = inputProcessor.invalidInputCommandResponder(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], clientID);
    ASSERT_EQ(responseDTO.command, "INVALID INPUT COMMAND");
    ASSERT_EQ(responseDTO.data, "");
}

// Need to implement;
TEST(InputProcessor, processInvalidCommand) {
    
};





