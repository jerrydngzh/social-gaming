#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <vector>
#include <iostream>
#include "Server.h"

namespace net = boost::asio;
namespace beast = boost::beast;
using tcp = boost::asio::ip::tcp;

// uniquely identified by ints for now
std::vector<int> clients;
std::vector<int> games;


/*
The server should handle the following:
1. Accept connections from clients
2. Receive requests from clients
3. Process requests from clients
4. Send responses to clients

Nick's web-socket-networking demo demonstrates a single-threaded event loop
that sends and receives async 
- it makes use of an "update()" that polls for batch of incoming requests
- perhaps can make use of this?
*/


int main(int argc, char* argv[]){
    
    if (argc != 2){
        std::cout << "Usage: ./server <port>" << std::endl;
        return EXIT_FAILURE;
    }
    int port = std::stoi(argv[1]);
    
    // TODO: integrate the following into Server object?
    // io_context represents the execution context of the program
    // tcp::acceptor reviews incomxing connections
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v6(), port));


    while (true){
        std::cout << "Waiting for connection..." << std::endl;
        // incoming_socket recieves new client connections
        tcp::socket incoming_socket(io_context);

        // acceptor.accept blocks till the connection is accepted
        acceptor.accept(incoming_socket);

        std::cout << "Connection accepted!" << std::endl;
        // incoming_socket.send(boost::asio::buffer("Hello from server!"));
        break;

        // TODO: generate a unique id for the client, append to list of active clients

        // TODO: wait for request from a client

        // TODO: process request

        // TODO: send response to client
 
        // TODO: handle client shutdown
    }
}
