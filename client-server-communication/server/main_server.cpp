/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Server.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>


using networking::Server;
using networking::Connection;
using networking::Message;


std::vector<Connection> clients;

/*
  handles connecting new clients
*/ 
void
onConnect(Connection c) {
  std::cout << "New connection found: " << c.id << "\n";
  clients.push_back(c);
}

/* 
  handles disconnecting clientss
*/
void
onDisconnect(Connection c) {
  std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}

struct MessageResult {
  std::string result;
  bool shouldShutdown;
};


// TODO: Game Server Logic
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
MessageResult
processMessages(Server& server, const std::deque<Message>& incoming) {
  std::ostringstream result;
  for (const auto& message : incoming) {
    // if (message.text == "quit") {
    //   server.disconnect(message.connection);
    // } else if (message.text == "shutdown") {
    //   std::cout << "Shutting down.\n";
    //   quit = true;
    // } else {
    //   result << message.connection.id << "> " << message.text << "\n";
    // }
    auto target = message.connection.id;
    auto loc = std::find(clients.begin(), clients.end(), target);
    if(loc != clients.end()) {
      auto connection = clients[std::distance(clients.begin(), loc)];
      result << connection << ", " << message.text << "\n";
    }

  }

  // TODO: messages are processed here
  return MessageResult{result.str(), quit};
}

/*
  Constructs outgoing messages to be sent to all respective clients
  ex: c1, c2, c3 belong to gameInstance1 
    - build a message to be sent to only c1, c2, c3 
*/
std::deque<Message>
buildOutgoing(const std::string& log) {
  std::deque<Message> outgoing;
  for (auto client : clients) {
    outgoing.push_back({client, log});
  }
  return outgoing;
}

// TODO: modify / remove handling the HTTP file
std::string
getHTTPMessage(const char* htmlLocation) {
  if (access(htmlLocation, R_OK ) != -1) {
    std::ifstream infile{htmlLocation};
    return std::string{std::istreambuf_iterator<char>(infile),
                       std::istreambuf_iterator<char>()};

  }

  std::cerr << "Unable to open HTML index file:\n"
            << htmlLocation << "\n";
  std::exit(-1);
}


int
main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002\n";
    return 1;
  }

  const unsigned short port = std::stoi(argv[1]);

  // TODO: modify httpmessage
  Server server{port, onConnect, onDisconnect};

  while (true) {
    bool errorWhileUpdating = false;
    try {
      server.update();
    } catch (std::exception& e) {
      std::cerr << "Exception from Server update:\n"
                << " " << e.what() << "\n\n";
      errorWhileUpdating = true;
    }

    const auto incoming = server.receive();
    const auto [log, shouldQuit] = processMessages(server, incoming);
    const auto outgoing = buildOutgoing(log);
    server.send(outgoing);

    if (shouldQuit || errorWhileUpdating) {
      break;
    }

    sleep(1);
  }

  return 0;
}

