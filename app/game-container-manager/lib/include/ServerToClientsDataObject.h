#pragma once

#include <string>
#include <vector>

/* ServerToClientsDataObject
    - What it's For:
     It is used to neatly package data, generated by something on the server application,
     to be sent to some list of Client applications.
    - How to Use:
     ServerToClientsDataObject should be constructed whenever the server needs to send data back to one or more clients.
*/

struct ServerToClientsDataObject
{
    std::vector<uintptr_t> clientIDs;
    std::string command;
    std::string data;

    ServerToClientsDataObject() {};
    ServerToClientsDataObject(const std::vector<uintptr_t> clientIDs, const std::string command, const std::string data)
        : clientIDs(clientIDs), command(command), data(data) {}

    // NOTE: a DTO shouldn't have any logic, but this is just for debugging
    void printData() const
    {
        std::cout << "ClientIDs: ";
        for (const auto &clientID : clientIDs)
        {
            std::cout << clientID << " ";
        }
        std::cout << ", command: " << command << ", data: " << data << std::endl;
    }
};
