#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameContainerManager.h"


TEST(gameContainerManager, POC) {
    EXPECT_TRUE(true);
} // POC

TEST(DummyTestSuite, DummyTest) {
    // Arrange 
    int x = 1;
    int result = 0;

    // Act 
    result = x + 1;

    // Assert 
    EXPECT_EQ(result, 2);
}

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


TEST(ComponentTest, CreateGameContainer){

    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    ASSERT_EQ(containerID, 0);
    ASSERT_TRUE(gameContainerManager.doesGameContainerIDExist(containerID));
}



TEST(gameContainerManagerTest, CreateGameContainer){

    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    ASSERT_EQ(containerID, 0);
};

// TEST(gameContainerManagerTest, DoesGameContainerIDExist_Success){

//     GameContainerManager gameContainerManager;
//     int containerID = gameContainerManager.createGameContainer();
//     ASSERT_TRUE(gameContainerManager.doesGameContainerIDExist(containerID));
// };

TEST(GameContainerManagerTest, DoesGameContainerIDExist_Failure) {
    int containerID = 42;  
    GameContainerManager gameContainerManager;
    bool exists = gameContainerManager.doesGameContainerIDExist(containerID);
    ASSERT_FALSE(exists);
};

TEST(GameContainerManagerTest, addPlayerToGame) { 
    GameContainerManager gameContainerManager;
    int clientID = 1;
    int containerID = gameContainerManager.createGameContainer();
    std::string result = gameContainerManager.addPlayerToGame(clientID, containerID);
    std::string expected = "client id " + std::to_string(clientID) + " added to game " + std::to_string(containerID) + "\n";
    ASSERT_EQ(result, expected);
};

TEST(GameContainerManagerTest, GiveGameContainerPlayerInput) {    
    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    int clientID = 1;
    std::string inputData = "Some input data";
    std::string result = gameContainerManager.giveGameContainerPlayerInput(containerID, clientID, inputData);
    std::string expected = "gameContainer " + std::to_string(containerID) + " received player " + std::to_string(clientID) + " input: " + inputData + "\n";
    ASSERT_EQ(result, expected);   
};

TEST(ClientsManagerTest, IsClientPlayer_Positive) {  
    int clientID = 1;
    int clientGameCode = 0;
    ClientsManager clientsManager;
    clientsManager.addPlayerToGame(clientID, clientGameCode);
    bool isPlayer = clientsManager.isClientPlayer(clientID);
    ASSERT_TRUE(isPlayer);
};

TEST(ClientsManagerTest, IsClientPlayer_Negative) {
    int clientID = 1;
    ClientsManager clientsManager;
    bool isPlayer = clientsManager.isClientPlayer(clientID);
    ASSERT_FALSE(isPlayer);
};

TEST(ClientsManagerTest, GetGameContainerIDofPlayer) {
    int clientID = 1;
    int gameContainerID = 42; 
    ClientsManager clientsManager;
    clientsManager.addPlayerToGame(clientID, gameContainerID);
    int retrievedGameContainerID = clientsManager.getGameContainerIDofPlayer(clientID);
    ASSERT_EQ(retrievedGameContainerID, gameContainerID);
};


//Maybe add a GetOwnerofGameContainer function
//Also, initialize ownerIDtoGameIDMap in ClientsManager constructor
TEST(ClientsManagerTest, SetOwnerOfGameContainer) {
    int clientID = 1;
    int gameContainerID = 42; // A random game container ID
    ClientsManager clientsManager;
    clientsManager.setOwnerOfGameContainer(clientID, gameContainerID);
    // ASSERT_TRUE(clientsManager.ownerIDtoGameIDMap.find(clientID) != clientsManager.ownerIDtoGameIDMap.end());
    // ASSERT_EQ(clientsManager.ownerIDtoGameIDMap[clientID], gameContainerID);
};

//Fix IscreateCommandValid stub 
TEST(CreateProcessor, processCreateCommand) {
    C2SDTO requestDTO;
    requestDTO.clientID = 1;
    requestDTO.command = "create";
    requestDTO.data = "Some create data";

    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    CreateProcessor createProcessor(gameContainerManager, clientsManager);
    S2CDTO responseDTO = createProcessor.processCreateCommand(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "create");
    ASSERT_EQ(responseDTO.data, "Response data from createGame");
};

//Fix IscreateCommandValid stub 
TEST(CreateProcessor, isCreateCommandValid) {
    
};


TEST(CreateProcessor, createGame) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    CreateProcessor createProcessor(gameContainerManager, clientsManager);

    C2SDTO requestDTO;
    requestDTO.clientID = 1;
    requestDTO.command = "create";
    requestDTO.data = "Some create data";

    // S2CDTO responseDTO = createProcessor.createGame(&requestDTO);
    S2CDTO responseDTO;
    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "CREATE ROOM COMMAND SUCCESS");
    ASSERT_FALSE(responseDTO.data.empty());

};
//It's a stub function
TEST(CreateProcessor, invalidCreateCommandResponder) {
    
};

TEST(JoinProcessor, processJoinCommand) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    C2SDTO requestDTO;
    requestDTO.clientID = 1;
    requestDTO.command = "join";
    requestDTO.data = "123";

    S2CDTO responseDTO = joinProcessor.processJoinCommand(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "JOIN ROOM COMMAND SUCCESS");
    
    ASSERT_FALSE(responseDTO.data.empty()); 
};

TEST(JoinProcessor, gameContainerExists) {

    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    int existingGameContainerID = gameContainerManager.createGameContainer();
    // bool exists = joinProcessor.gameContainerExists(existingGameContainerID);
    // ASSERT_TRUE(exists);
};

TEST(JoinProcessor, isClientAlreadyPlayer) {
    
    ClientsManager clientsManager;
    GameContainerManager gameContainerManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    int clientID = 1;
    int gameContainerID = 456; 
    clientsManager.addPlayerToGame(clientID, gameContainerID);

    // bool alreadyPlayer = joinProcessor.isClientAlreadyPlayer(clientID);
    // ASSERT_TRUE(alreadyPlayer);
};

TEST(JoinProcessor, isJoinCommandValid) {
    
};

TEST(JoinProcessor, joinGame) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    C2SDTO requestDTO;
    requestDTO.clientID = 1;
    requestDTO.command = "join";
    requestDTO.data = "123"; 

    S2CDTO responseDTO = joinProcessor.processJoinCommand(requestDTO);

    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_EQ(responseDTO.command, "JOIN ROOM COMMAND SUCCESS");
    
    ASSERT_FALSE(responseDTO.data.empty()); 
    
};

TEST(JoinProcessor, invalidJoinCommandResponder_ClientAlreadyPlayer) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    int existingGameContainerID = gameContainerManager.createGameContainer();
    int clientID = 1;

    // Add the player to the game (simulate a client already being a player)
    clientsManager.addPlayerToGame(clientID, existingGameContainerID);

    C2SDTO requestDTO;
    requestDTO.clientID = clientID;
    requestDTO.command = "join";
    requestDTO.data = std::to_string(existingGameContainerID);

    S2CDTO responseDTO;
    // S2CDTO responseDTO = joinProcessor.invalidJoinCommandResponder(requestDTO);

    ASSERT_EQ(responseDTO.command, "INVALID JOIN COMMAND");
    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_TRUE(responseDTO.data.find("Client " + std::to_string(requestDTO.clientID) + " is already a Player.") != std::string::npos);
    ASSERT_FALSE(responseDTO.data.empty()); // There should be an error message
};

TEST(InputProcessor, processInputCommand) {
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
    
    int existingGameContainerID = gameContainerManager.createGameContainer();
    int clientID = 1;

    clientsManager.addPlayerToGame(clientID, existingGameContainerID);

    C2SDTO requestDTO;
    requestDTO.clientID = clientID;
    requestDTO.command = "input";
    requestDTO.data = "Some input data";

    S2CDTO responseDTO = inputProcessor.processInputCommand(requestDTO);

    ASSERT_EQ(responseDTO.command, "VALID INPUT COMMAND");
    ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    ASSERT_EQ(responseDTO.clientIDs[0], requestDTO.clientID);
    ASSERT_TRUE(responseDTO.data.find("Game Container " + std::to_string(existingGameContainerID) +
                                      " received player " + std::to_string(requestDTO.clientID) +
                                      " input: " + requestDTO.data) != std::string::npos);
};

TEST(InputProcessor, isClientPlayer) {
    
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
        
    int clientID = 1;
    int gameContainerID = gameContainerManager.createGameContainer();

    clientsManager.addPlayerToGame(clientID, gameContainerID);

    // bool isPlayer = inputProcessor.isClientPlayer(clientID);

    // ASSERT_TRUE(isPlayer);
};

TEST(InputProcessor, isInputCommandValid) {
       
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
        
    int clientID = 1;
    int gameContainerID = gameContainerManager.createGameContainer();

    clientsManager.addPlayerToGame(clientID, gameContainerID);

    C2SDTO requestDTO;
    requestDTO.clientID = clientID;
    requestDTO.command = "input";
    requestDTO.data = "Some input data";

    // bool isValid = inputProcessor.isInputCommandValid(requestDTO);

    // ASSERT_TRUE(isValid);
};

TEST(InputProcessor, invalidInputCommandResponder) {

    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
 
    int clientID = 1;
    int gameContainerID = gameContainerManager.createGameContainer();

    clientsManager.addPlayerToGame(clientID, gameContainerID);

    C2SDTO requestDTO;
    requestDTO.clientID = clientID;
    requestDTO.command = "invalid_input";
    requestDTO.data = "Some invalid input data";

    // S2CDTO responseDTO = inputProcessor.invalidInputCommandResponder(requestDTO);

    //  ASSERT_EQ(responseDTO.clientIDs.size(), 1);
    // ASSERT_EQ(responseDTO.clientIDs[0], clientID);
    // ASSERT_EQ(responseDTO.command, "INVALID INPUT COMMAND");
    // ASSERT_EQ(responseDTO.data, "");
};

//stub 
TEST(InputProcessor, processInvalidCommand) {
    
};





