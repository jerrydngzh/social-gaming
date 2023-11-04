/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Client.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: \n  " << argv[0] << " <ip address> <port>\n"
              << "  e.g. " << argv[0] << " localhost 8080\n";
    return 1;
  }

  networking::Client client{argv[1], argv[2]};

  bool done = false;
  auto onTextEntry = [&done, &client] (std::string text) {
    if ("exit" == text || "quit" == text) {
      done = true;
    } else {
      client.send(text);
    }
  };

  while (!done && !client.isDisconnected()) {
    try {
      client.update();
    } catch (std::exception& e) {
      std::cout << "Exception from Client update: " << e.what() << std::endl;
      done = true;
    }

    auto response = client.receive();
    if (!response.empty()) {
        std::cout << response << std::endl;
    }

    // send a message to the server
    // NOTE: cin is blocking, any incoming messages from server
    //       will not display till after a message is sent (i.e. unblock from cin)
    // TODO: figure out how to get non-blocking input
    std::string entry;
    std::cin >> entry;
    onTextEntry(entry);
  }

  return 0;
}
