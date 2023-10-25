#pragma once
#include <string>

class Server {
    public:
        Server();
        Server(int port);
        ~Server();

        std::string receiveRequest();

        /*
            the server should be able to stop in the middle of processing the request
            - if some timer runs out for the request before it's finished
                OR i/o is required from the client
            - a "bookmark" is created to keep track of where it left off
                - ex: halfway through traversing the rules-tree, bookmark the current node
            - save the bookmark & request in a queue for the next "update?"

            Considerations:
                - queued requests should be processed in order?
                - how to handle invalid requests?
        */
        std::string processRequest();

        /*
            the server should be able to send a response to the client
            - response can be request invalid, completed, queued {io or timer}
        */
        void sendResponse();

    private:
        int port;
};