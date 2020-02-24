#pragma once

#include "server.h"
#include "client.h"

class ThreadedServer : public Server {
    public:
        ServerReadListener* read;

        ThreadedServer(char* input_ip, int port) : Server(input_ip, port){
            read = new ServerReadListener(this);

        }

        void waitForConnectionsAndRead() {
            read->start();
        }
};

class ThreadedClient : public Client {
    public:
        ClientListener* listen;

        ThreadedClient(char* input_ip, int port, char* server_ip, int server_port) : Client(input_ip, port, server_ip, server_port){
            listen = new ClientListener(this);
         }

        void readMessages() {
            listen->start();
        }
};