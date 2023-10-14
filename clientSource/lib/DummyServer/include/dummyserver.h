#include <string>

class DummyServer {
public:
    DummyServer();

    // process should read message_from_client, and write a message_for_client accordingly.
    void process();

    // reads the message in serverMailbox - from client to server. 
    void getMessage(std::string message);
    // writes a message from the server into clientMailbox - from server to client. 
    std::string setMessage();
    
private:
    // pick a random move for the server as an "AI" opponent
    std::string randomMove();

    // generates a game code
    int generateGameCode();
    // takes the two moves, plays rps, and returns the winner 
    std::string gameResult(std::string player1Move, std::string player2Move);
    
    std::string play();

    std::string messageForClient;
    std::string messageFromClient;
};