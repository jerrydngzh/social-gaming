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

## Andy's Dev Notes 
Join 
- user input works
- draw works
- when draw does not work, issue.

Create leads to server and client processing, then an error
libc++abi: terminating due to uncaught exception of type std::out_of_range: basic_string