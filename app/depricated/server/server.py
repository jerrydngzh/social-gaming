# Server 
# 1. Recieve Message from All Clients
# 2. Concatenate All Messages
# 3. Broadcast Results to All Clients 

import time

def server2():
    print("Server: Hello, Server Rack!")

    client1_message = ""
    client2_message = ""
    client3_message = ""

    recieved_message_from_client1 = False
    recieved_message_from_client2 = False
    recieved_message_from_client3 = False
    recieved_messages_from_all_clients = False 

    # 1. Recieve Message from All Clients
    while recieved_messages_from_all_clients == False:
        time.sleep(1)  # Wait for 1 second
        # print("Server: waiting to recieve messages from all clients")

        # check if client1 sent message
        with open('client1-to-server.txt', 'r') as file:
            file_content = file.read()
            if not file_content:
                # File is empty, continue the loop
                recieved_message_from_client1 = False  
            else:
                # If the file is not empty, read its content and empty it.
                recieved_message_from_client1 = True
                client1_message = file_content
                print("Server: recieved message from client1!")

        # if recieved_message_from_client1:
        #     with open('client1-to-server.txt', 'w') as file:
        #         file.truncate(0)


        # check if client2 sent message
        with open('client2-to-server.txt', 'r') as file:
            file_content = file.read()
            if not file_content:
                # File is empty, continue the loop
                recieved_message_from_client2 = False  
            else:
                # If the file is not empty, read its content and empty it.
                recieved_message_from_client2 = True
                client2_message = file_content
                print("Server: recieved message from client2!")

        # if recieved_message_from_client2:
        #     with open('client2-to-server.txt', 'w') as file:
        #         file.truncate(0)

        
        # check if client3 sent message
        with open('client3-to-server.txt', 'r') as file:
            file_content = file.read()
            if not file_content:
                # File is empty, continue the loop
                recieved_message_from_client3 = False  
            else:
                # If the file is not empty, read its content and empty it.
                recieved_message_from_client3 = True
                client3_message = file_content
                print("Server: recieved message from client3!")

        # if recieved_message_from_client3:
        #     with open('client3-to-server.txt', 'w') as file:
        #         file.truncate(0)

        # check if recieved_messages_from_all_clients
        if recieved_message_from_client1 and recieved_message_from_client2 and recieved_message_from_client3:
            print("broken?")
            recieved_messages_from_all_clients = True

    print("Server: recieved message from all clients!")

    # 2. Concatenate All Messages
    client_messages = client1_message + " " + client2_message + " " + client3_message
    print("Server: broadcasting message to clients!")

    # 3. Broadcast Results to All Clients 
    with open('server-to-client1.txt', 'w') as f:
        f.write(client_messages)
    
    with open('server-to-client2.txt', 'w') as f:
        f.write(client_messages)

    with open('server-to-client3.txt', 'w') as f:
        f.write(client_messages)


    with open('client1-to-server.txt', 'w') as file:
        file.truncate(0)

    with open('client2-to-server.txt', 'w') as file:
        file.truncate(0)

    with open('client3-to-server.txt', 'w') as file:
        file.truncate(0)

server2()