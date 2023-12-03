#include "ServerManager.h"

const char *htmlLoc = "./app/server-platform/index.html";


ServerManager::ServerManager(const unsigned short port)
    : gameContainerManager(), clientsManager(), createProcessor(this->gameContainerManager, this->clientsManager),
      joinProcessor(this->gameContainerManager, this->clientsManager), invalidCommandProcessor(),
      inputProcessor(this->gameContainerManager, this->clientsManager)
{
    this->server = std::make_unique<Server>(
        port, getHTTPMessage(htmlLoc),
        [this](networking::Connection c)
        { this->onConnect(c); },
        [this](networking::Connection c)
        { this->onDisconnect(c); });

    this->messageProcessors = std::make_unique<MessageProcessors::MessageProcessor>();
}

void ServerManager::startServer()
{
    while (true)
    {
        bool errorWhileUpdating = false;
        try
        {
            this->server->update();
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception from Server update:\n"
                      << " " << e.what() << "\n\n";
            errorWhileUpdating = true;
        }
        const auto incoming = this->server->receive();

        const auto incomingMessages = processMessages(incoming);

        // single execution of requests based on batch of incoming messages
        for (const auto &request : incomingMessages)
        {   
            // const auto messageResult = this->serverProcessor->execute(incomingMessages);
            // const auto outgoing = buildOutgoing(messageResult);
            // this->server->send(outgoing);

            // NOTE: ServerProcessor execution control flow is inlined 
            // into ServerManager, as opposed to a separate class.
            C2SDTO requestDTO = messageDTOToServerProcessorDTO(request);
            S2CDTO responseDTO;

            /* TODO: 
                Encapsulate Command Processing in its own Class. 
                Create Map To automate the switch case - so that this code 
                does not need to be rewritten every single time we add a new command processor. 
            */ 
            // Figures out what process to run depending on the `command`
            Command command = InputCommandMap[requestDTO.command];
            switch (command)
            {
                case Command::CREATE:
                    responseDTO = createProcessor.processCreateCommand(requestDTO);
                    break;
                case Command::JOIN:
                    responseDTO = joinProcessor.processJoinCommand(requestDTO);
                    break;
                case Command::INPUT:
                    responseDTO = inputProcessor.processInputCommand(requestDTO);
                    break;
                default:
                    responseDTO = invalidCommandProcessor.processInvalidCommand(requestDTO);
                    break;
            }

            std::deque<MessageProcessors::ResponseMessageDTO> responses = serverProcessorDTOToMessageDTO(responseDTO);

            const auto outgoing = buildOutgoing(responses);
            this->server->send(outgoing);
        }

        if (errorWhileUpdating)
        {
            break;
        }
    }
}

void ServerManager::onConnect(networking::Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    clients.push_back(c);

    std::deque<Message> outgoing;
    std::string_view outgoingCommand = OutputCommandMap[Command::NEW_CONNECTION]; 

    MessageProcessors::ResponseMessageDTO response;
    std::stringstream message;
    message << "Welcome to the server!" << std::endl
            << "Please enter one of the following commands to interact with the server:" << std::endl
            << "1. \"" << OutputCommandMap[Command::CREATE] << "\"" << std::endl 
            << "\t -> To create a new game room." << std::endl
            << "2. \"" << OutputCommandMap[Command::JOIN] <<  " <room-code>\"" <<  std::endl
            << "\t -> To join an existing game room." << std::endl;

    response.clientId = c.id;
    response.messageStatus = true;
    response.messageResult = message.str();
    response.command = outgoingCommand;
    response.commandData = outgoingCommand;

    outgoing.push_back({c, message.str()});
    server->send(outgoing);
}

void ServerManager::onDisconnect(networking::Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    clients.erase(eraseBegin, std::end(clients));
}

std::string
ServerManager::getHTTPMessage(const char *htmlLocation)
{
    if (access(htmlLocation, R_OK) != -1)
    {
        std::ifstream infile{htmlLocation};
        return std::string{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
    }
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
}

std::deque<MessageProcessors::RequestMessageDTO>
ServerManager::processMessages(const std::deque<Message> &incoming)
{
    std::deque<MessageProcessors::RequestMessageDTO> requests;
    for (const auto &message : incoming)
    {
        Connection target{message.connection.id};
        auto loc = std::find(clients.begin(), clients.end(), target);

        if (loc != clients.end())
        {
            Connection connection = clients[std::distance(clients.begin(), loc)];
            std::cout << "Message from " << connection.id << ": " << message.text << "\n";

            MessageProcessors::RequestMessageDTO request = messageProcessors->processIncomingMessage(message.text);
            Command command = InputCommandMap[request.command];

            if (command == Command::DISCONNECT)
            {
                this->server->disconnect(connection);
            }
            else
            {
                request.clientId = connection.id;
                requests.push_back(request);
            }
        }
        else
        {
            std::cout << "Connection: "
                      << message.connection.id
                      << " not found!\n";
            requests.push_back(MessageProcessors::RequestMessageDTO{message.connection.id, "Connection not found!"});
        }
    }
    return requests;
}

std::deque<Message>
ServerManager::buildOutgoing(const std::deque<MessageProcessors::ResponseMessageDTO> &responses)
{
    std::deque<Message> outgoing;
    for (const auto &response : responses)
    {
        Connection target{response.clientId};
        auto loc = std::find(clients.begin(), clients.end(), target);

        if (loc != clients.end())
        {
            Connection connection = clients[std::distance(clients.begin(), loc)];
            auto message = messageProcessors->processOutgoingMessage(response);
            outgoing.push_back({connection, message});
        }
        else
        {
            std::cout << "Connection: "
                      << response.clientId
                      << " not found!\n";
        }
    }
    return outgoing;
}

C2SDTO ServerManager::messageDTOToServerProcessorDTO(const MessageProcessors::RequestMessageDTO &message)
{
    C2SDTO requestDTO;
    requestDTO.clientID = message.clientId;
    requestDTO.command = message.command;
    requestDTO.data = message.data;
    return requestDTO;
}

std::deque<MessageProcessors::ResponseMessageDTO> ServerManager::serverProcessorDTOToMessageDTO(const S2CDTO &message)
{
    std::deque<MessageProcessors::ResponseMessageDTO> responses;

    // a response may require sending of the same message to multiple clients of a game room
    // so we need to iterate through the list of client IDs and create a response for each
    for (const auto clientId : message.clientIDs)
    {
        std::cout << "Client ID: " << clientId << std::endl; // TESTING ONLY
        MessageProcessors::ResponseMessageDTO responseDTO;
        responseDTO.clientId = clientId;
        responseDTO.command = message.command;
        responseDTO.commandData = message.data;
        responses.push_back(responseDTO);
    }
    return responses;
}
