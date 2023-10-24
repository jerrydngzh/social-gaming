# STORY: User Creates Game  

This story describes the sequence of events that should occur when a user decides to create a game.  
Bolded Text (Two asterix) is text from Nick's Social Game Platform Description on Coursys. 

**When a user connects to the game server, they may either join a game or create a new game amongst those served**

1. Client asks User to Create Game OR Join Game 
2. Player chooses to Create Game 

**When a new game is created, it may be configured by the creating player,**

3. Client asks player for game config file (SocialGame)
4. Client sends SocialGame (and User ID) to Server 

5. Server constructs a GameRoom (Holds info on clients playing game) and a Game (Purely based on SocialGameFile)

**The creating player is designated as the “owner” of the game session and will have admin controls over the game.**

6. Server sets GameRoom Owner as UserID of the user who created the game, which gives that user admin controls. 

**The owner may configure the game and create it, after which they will receive an “invite code”.** 

7. Server generates GameRoomInviteCode 

8. Server sends GameRoomInviteCode to Client
9. Client tells the User the GameRoomInviteCode

**Note, the owner of the game need not be a player. If they wish to play the game, they may also join.**

10. User may choose to join a game 

---

## SubStory: Send SocialGame File to Server 

This story describes in greater detail how a game is configured by the creating player. 
It goes in depth steps 3 and 4 of the Story above. 

**When a new game is created, it may be configured by the creating player,**

1. Client asks player for game config file (SocialGame)
2. Client sends SocialGame (and User ID) to Server 
3. Server Acknowledges that it has recieved the SocialGame file. 

# Andy 
string filePath askPlayerGameConfigFile() {
    cout give me the game config filePath 
    cin filePath 
    return filePath
}

# Kamal
string fileContent getFile(filePath) {
    string fileContent;
    
    for line in read(filePath)
        fileContent.append(line)
    
    return fileContent;
}

client.sendToServer(fileContent) 

Client-Side
===
Server-Side

fileContent = server.recieveFromClient()

void fileContentToGameFile(fileContent) {
    string filepath

    for line in read(fileContent)
        filepath.write(line)

}
