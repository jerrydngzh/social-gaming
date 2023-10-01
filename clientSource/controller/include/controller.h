#include <string>

// Spike server code from: https://github.com/nsumner/web-socket-networking
// in developing endpoints for the controller to backend
// #include <boost> 

class Controller {
public:
    Controller(const std::ifstream& jsonFile);
    
    // POST
    std::string sendPlayerResponse(const std::string&);

    // POST
    std::string createGame(const std::string&);

private:
    const std::unique_ptr<std::ifstream> jsonFile;
}