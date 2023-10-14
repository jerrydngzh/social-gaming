#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

/* Class */
class DummyServer {
public:
    DummyServer() {};

    // process should read message_from_client, and write a message_for_client accordingly.
    void process() {
        // Simulate server processing
        std::cout << "Server processing..." << std::endl;

        if (message_from_client == "") {
            // do nothing 
        } else {
            
            if (message_from_client == "create") {
                int game_code = generateGameCode();
                std::string game_code_string = std::to_string(game_code);
                message_for_client = "game_code " + game_code_string;
            }
            
            if (message_from_client == "join") {
                message_for_client = "game_instruction user input rock paper or scissors.";
            }

            if (message_from_client == "rock" || message_from_client == "paper" || message_from_client == "scissors") {
                message_for_client = play();
            }
        }

    }

    // reads the message in server_mailbox - from client to server. 
    void read_message(std::string message) {
        message_from_client = message;
    }

    // writes a message from the server into client_mailbox - from server to client. 
    std::string write_message() {
        return message_for_client;
    }
    
private:
    // pick a random move for the server as an "AI" opponent
    std::string randomMove() {
        int random = std::rand() % 3; 
        switch(random) {
            case 0: return "rock";
            case 1: return "paper";
            case 2: return "scissors";
        }
        // default in case random doesn't work
        return "rock";
    }

    // generates a game code
    int generateGameCode() {
        std::srand(std::time(0));
        int randomGameCode = (std::rand() % 10);
        return randomGameCode;
    }
    
    // takes the two moves, plays rps, and returns the winner 
    std::string gameResult(std::string player1Move, std::string player2Move) {
        if  (player1Move == player2Move) {
            return "draw";
        }
        if  (player1Move == "rock" && player2Move == "paper") {
            return "player2";
        }
        if  (player1Move == "paper" && player2Move == "scissors") {
            return "player2";
        }
        if  (player1Move == "scissors" && player2Move == "rock") {
            return "player2";
        }
        if  (player1Move == "paper" && player2Move == "rock") {
            return "player1";
        }
        if  (player1Move == "scissors" && player2Move == "paper") {
            return "player1";
        }
        if  (player1Move == "rock" && player2Move == "scissors") {
            return "player1";
        }
        // Handle the case when the input is invalid
        return "invalid";
    }
    
    std::string play() {
        std::string p1 = message_from_client;
        std::string p2 = randomMove();
        std::string result = gameResult(p1, p2);
        if (result == "draw") {
            std::string server_message = "";
            server_message = "game_instruction ";
            server_message += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
            server_message += "Draw! Enter rock, paper, or scissors";
            return server_message; 
        } else {
            std::string server_message = "";
            server_message = "game_over ";
            server_message += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
            server_message += "Winner! " + result + "\n";
            return server_message;
        }
    }

    std::string message_for_client;
    std::string message_from_client;
};

/* Class */
class DummyClient {
public:
    DummyClient() {
        bool choice = create_or_join_game();
        if (choice) {
            message_for_server = "create";
        } else {
            message_for_server = "join";
        }
    };

    bool create_or_join_game() {
        std::cout << "create or join game?: create | join : "; 
        
        std::string user_choice; 
        std::cin >> user_choice;

        if (user_choice == "create") {
            return true;
        } 
        
        return false;
    }

    void process() {
        // Simulate client processing
        std::cout << "Client processing..." << std::endl;
        
        if (message_from_server == "") {
            // do nothing 
        } else {
            std::string prefix_command = ""; 
            prefix_command = get_string_prefix(message_from_server);

            if(prefix_command == "game_code") {
                run_game_code();
            } else if (prefix_command == "game_instruction") {
                // print game instructions 
                run_game_instruction();
                // Getting User Move 
                std::cin >> message_for_server;
            } else if (prefix_command == "game_over") {
                std::cout << message_from_server << "\n";
                // then exits program
                exit(0);
            }
        }
    }

    // reads the message in client_mailbox - from server to client. 
    void read_message(std::string message) {
        message_from_server = message;
    }

    // writes a message from the client into server_mailbox - from client to server. 
    std::string write_message() {
        return message_for_server;
    }

    std::string get_string_prefix(const std::string& message) {
        std::istringstream iss(message); 
        std::string prefix;
        iss >> prefix; 
        return prefix;
    }

    void run_game_code() {
        std::istringstream iss(message_from_server);
        std::string firstWord, secondWord;
        
        // Extract the first word
        iss >> firstWord;
        
        // Extract the second word
        iss >> secondWord;
        
        std::string game_code = secondWord;

        std::cout << "The game code is " << game_code << "\n";

        std::cout << "Join Game?: yes | no : "; 
        
        std::string user_choice; 
        std::cin >> user_choice;

        if (user_choice == "yes") {
            message_for_server = "join";
        } else {
            exit(0);
        }
    }

    void run_game_instruction() {
        std::string game_instruction = "";

        // Find the position of the first space
        size_t firstSpacePos = message_from_server.find(' ');

        if (firstSpacePos != std::string::npos) {
            // Remove the first word
            game_instruction = message_from_server.substr(firstSpacePos + 1);
        } else {
            // Handle the case when there are no spaces in the string
            game_instruction = "";
        }

        std::cout << game_instruction << "\n";
    }

private:
    std::string message_for_server; // join, create.
    std::string message_from_server; // game_code 1314, game_instruction user input rock paper or scissors. 
};

int main() {
    DummyClient client;
    DummyServer server;

    std::string client_mailbox = "";
    std::string server_mailbox = "";

    while (true) {
        server.process();
        client_mailbox = server.write_message(); // game_instruction user input rock paper or scissors.

        client.read_message(client_mailbox);
        client.process();

        server_mailbox = client.write_message(); // join, create
        server.read_message(server_mailbox);
    }

    return 0;
}