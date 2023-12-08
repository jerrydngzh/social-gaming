#include <iostream>
#include <unistd.h>

#include "ClientManager.h"
#include "ChatWindow.h"

/*
TODO: 
- add the main screen display
    - enter a name
    - (C) to create a game
      - supply a game file (via file directory)
      - get list of available games
    - (J) to join a game
*/
int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: \n  " << argv[0] << " <ip address> <port>\n"
              << "  e.g. " << argv[0] << " localhost 8080\n";
    return 1;
  }

  char* ip = argv[1];
  std::string_view ipAddress(ip);
  ClientManager clientManager(ipAddress, argv[2]);
  clientManager.startClient();
  return 0;
}
