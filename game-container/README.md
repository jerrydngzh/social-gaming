
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