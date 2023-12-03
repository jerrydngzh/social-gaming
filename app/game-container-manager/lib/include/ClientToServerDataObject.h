#include <string>

/* ClientToServerDataObject
    - What it's For: It is used to provide an easy-to-access data object filled with data sent from a client application.
    - How to Use: Each of the fields can be accessed using ClientToServerDataObject.fieldName
    Note: If you are thinking of modifying the ClientToServerDataObject,
    you probably are trying to construct a ServerToClientsDataObject instead.
*/

struct ClientToServerDataObject
{
    const uintptr_t clientID;
    const std::string command;
    const std::string data;

    ClientToServerDataObject(const uintptr_t clientID, const std::string command, const std::string data)
    : clientID(clientID), command(command), data(data) {}

    void printData() const {
        std::cout << "clientID: " << clientID << ", command: " << command << ", data: " << data << std::endl;
    }
};
