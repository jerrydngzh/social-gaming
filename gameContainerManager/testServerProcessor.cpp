// When create game is called, a new game is created.

    // Arrange 
    // - make dto = Create Game DTO 

    // Act 
    // serverProcessor.processCommand(dto)

    // Assert 
    // serverProcessor.games.size() == 1


// When a join is requested, we check that the game exists

    // Arrange 
    // make join dto 

    // Act 
    // serverProcessor.processCommand(dto)

    // Assert 
    // returns join error due to game not existing 

// When a join is requested, the client is not already a player of another game
    // Arrange 
    // make game dto with client1
    // serverProcessor.processCommand(dto)

    // join game dto with client1
    // serverProcessor.processCommand(dto)

    // Act 
    // make game2 dto with client 1
    // serverProcessor.processCommand(dto)
    // join game2 dto with client1
    // serverProcessor.processCommand(dto)

    // Assert 
    // returns join error, as client already player of another game 


// When Create Game, client creating game becomes owner
    // Arrange 
    // make game dto with client1

    // Act 
    // serverProcessor.processCommand(dto)

    // Assert 
    // serverProcessor.owners has client1, game


// When client Input, client is a player of game.
    // Arrange 
    // make input dto with client1

    // Act 
    // serverProcessor.processCommand(dto)

    // Assert 
    // error = client not player of game 
