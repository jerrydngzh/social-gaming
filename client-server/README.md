Hello Team!

Hello, 

client_mailbox = ""
server_mailbox = "" 

DummyServer
    get_server_mail()
    ... 
    send_client_mail()

DummyClient
    get_client_mail()
        client_mail = client_mailbox

    send_server_mail()
        server_mailbox = "Rock"

# Components 
1. Client-Server Communication
2. Client Logic
3. Server Logic

Server Class + ServerMailHandler Class 
Client Class + ClientMailHandler Class 


# Single Player Game vs AI. 
# Story 1
client creates a game
    1. client requests game code from server
    2. server sends game code to client
    3. client asked whether they want to join game
    4. if yes, prompted for game code else exit()

# Story 2
Client joins a game
    1. client sends game code to server
    2. Server sends client a message - "Joined Game Room #"

# Story 3
Client plays rock paper scissors 
    1. client gets prompt from server to input a move 
    2. client gets user input move 
    3. client sends user input move to server 
    4. client gets results 
    - if draw, repeat steps 1-4
    - if game over, results are displayed
    session ends. 


# Build 
g++ -o main main.cpp
./main
