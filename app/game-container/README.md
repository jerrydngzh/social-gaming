
# Game will call them
# An
IO::requestInputChoice(String prompt, vector<String> choices, int timeout);
IO::requestInputText(String prompt, int timeout);
IO::requestInputRange(String prompt, pair<int> range, int timeout);
IO::requestInputVote(String prompt, vector<String> choices, int timeout);
IO::outputMessage(vector<Player> players, String message, int timeout);
IO::outputScores(vector<Scores> scores);



MAIN SERVER LOOP:
while true:
    Add any new games to our list of current games
    For each game:
        call clientServer who will check if all users have responded (or like game start initiated)
        if response is ready (all users responded or owner started game)
            send response to game container who will send it to game instance and it will start executing the
            game instance then eventually needs to request user input and pauses sending a request up to GameContainer and then GameContainerManager
            this game is now paused
            ClientServer sends the message to the users of that game

issue with this structure: game sends a message to players without needing a response
a solution: send out a message to clients then add a message response that just starts executing the game agian (like an empty response or a "message recieved response")

issue 2: The game instance needs a way to pause for x amount of time (timer function in rules)
a solution: the code that checks for messages received from clients will also check if timer expired and return to that game (response is ready) by again sending like an empty response or a "timer ended" response

GC outputMessage = game.startGame(...)
do some work on the DTO outputmessage
return outputMessage

GCM outputMessage = GC.sendMessageTo_Game( )
do some work on the DTO outputmessage
return outputMessage

CS outputMessage = GC.sendMessageTo_Game( )
work with message, send to clients

get new messages

GCM outputMessage = GC.sendMessageTo_Game( )

    GC outputMessage = game.startGame(...)

        run game then return next message

    do some work on the DTO outputmessage
    return outputMessage

do some work on the DTO outputmessage
return outputMessage

# 

# outputDTOContainingConfiguration = game.initialize(.game file path)
# outputDTOContainingConfiguration: struct of variables
# , 
# gameName

# inputDTOObject


# outputDTOContainngConfiguration =  vector of settings of type Setting(Setting class/Multiple Typess of Settings). playerRange (tuple of min and max),boolean hasAudience

# outputDTOContainingConfiguration = game.initialize(.game file path)
# Process configurations send back upward, also initialize 
# response = game.startGame(clientList, inputDTOConfiguration)

# if response has parallel just continue
# repsonse should have a boolean attached to say if its parallel or not

# response = game.resume(UpdatedDTOObject) which will return dto object
# dto object should be processed


# INPUTDTOOBJECT


//initialize, startgame, resume
// Configuration* initialize(filepath);
Configuration.rounds = response.value

// outMessage run()
// p

vector<Setting> settings

Setting getSettingByName(string in) {
    for each Setting s
        if s.name = in
        return s
}

for setting s in getSettings(){
    return REQUEST{s.name, s.kind, s.range[0], s.range[1]}
}


configuration.getSettingByName(clientResponse.name).setValue(clientResponse.value);

core-game-engine-build/_deps/**

# MAKE A LIST OF ALL SETTINGS TO EXPECT FROM ROCK PAPER SCISSIORS

Instead of sending whole setting object and letting client deal with it use the function for requesting user input

for each setting
send a DTO for a user request

DTO needs a way to let client know that we need to request a specific user to input either a number, a string, or a choice from multiple string (can have user input 1-5 to select an option or have them type in the right option maybe)