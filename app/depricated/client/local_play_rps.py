import time
import sys 
import random

# Client Class
class ClientMailHandler:
    def __init__(self):
        self.client_message = ""

    def process(self):
        user_input = input("Enter Input> ")
        self.client_message = user_input

    def write_message(self):
        return self.client_message
    
    def read_message(self, message: str):
        print("Server Message: ", message)


class Server:
    def __init__(self):
        self.game_over = False
        self.client_response = ""
        self.server_message = ""
    
    def play(self, player1_hand, player2_hand):
        if player1_hand == player2_hand:
            return "draw"
        if player1_hand == "rock" and player2_hand == "paper":
            return "player2"
        if player1_hand == "paper" and player2_hand == "scissors":
            return "player2"
        if player1_hand == "scissors" and player2_hand == "rock":
            return "player2"
        if player1_hand == "paper" and player2_hand == "rock":
            return "player1"
        if player1_hand == "scissors" and player2_hand == "paper":
            return "player1"
        if player1_hand == "rock" and player2_hand == "scissors":
            return "player1"

    def run_game(self):
        if self.game_over:
            sys.exit()

        if self.client_response == "":
            self.server_message = "Enter rock paper or scissors"
        else:
            player1_hand = self.client_response

            import random

            valid_moves = ["rock", "paper", "scissors"]
            player2_hand = random.choice(valid_moves)

            result = self.play(player1_hand, player2_hand)

            if result == "draw":
                self.server_message = f"Player1 Hand: {player1_hand} | Player2 Hand: {player2_hand} \n"
                self.server_message += "Draw! Enter rock paper or scissors"
            else:
                self.server_message = f"Player1 Hand: {player1_hand} | Player2 Hand: {player2_hand} \n"
                self.server_message += f"Game Over \n Winner is {result} \n Enter anything to exit \n"
                self.game_over = True
    

# Server Class
class ServerMailHandler:
    def __init__(self):
        self.server = Server()

    def process(self):
        self.server.run_game()

    def write_message(self):
        return self.server.server_message
    
    def read_message(self, message: str):
        self.server.client_response = message


def main():
    client = ClientMailHandler()
    server = ServerMailHandler()

    client_mailbox = ""
    server_mailbox = ""

    while(True):
        server.process()
        client_mailbox = server.write_message()

        client.read_message(client_mailbox)
        client.process()

        server_mailbox = client.write_message()
        server.read_message(server_mailbox)


main()
