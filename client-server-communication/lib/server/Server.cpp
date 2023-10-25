#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "include/Server.h"

Server::Server(int port) : port(port) {}

std::string Server::receiveRequest() {
    return "stub";
}

std::string Server::processRequest() {
    return "stub";
}

void Server::sendResponse() {}