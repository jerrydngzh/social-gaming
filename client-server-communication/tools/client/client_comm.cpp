/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Client.h"
#include "ChatWindow.h"

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

  ChatWindow chatWindow(onTextEntry);

  // TODO: display main page with instructions
  /*
    >> Welcome!
    >> Press (C) to create a game or (J) to join a game
    >> Press (quit or exit) to quit
  */

  while (!done && !client.isDisconnected()) {
    try {
      client.update();
    } catch (std::exception& e) {
      chatWindow.displayText("Exception from Client update:");
      chatWindow.displayText(e.what());
      done = true;
    }

    // display incoming messages from server
    auto response = client.receive();
    if (!response.empty()) {
      chatWindow.displayText(response);
    }

    // send a message to the server
    chatWindow.update();
  }

  return 0;
}
