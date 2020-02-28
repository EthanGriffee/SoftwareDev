#pragma once

#include "server.h"
#include "client.h"


/**
 * Creats a threaded server that uses one thread to read and the other to write
 */
class ThreadedServer : public Server {
    public:
        ServerReadListener* read;

        ThreadedServer(char* input_ip, int port) : Server(input_ip, port){
            read = new ServerReadListener(this);

        }
        /**
         * Starts the read thread
         */
        void waitForConnectionsAndRead() {
            read->start();
        }
};

/**
 * Creats a threaded client that uses one thread to read and the other to write
 */
class ThreadedClient : public Client {
    public:
        ClientListener* listen;

        ThreadedClient(char* input_ip, int port, char* server_ip, int server_port) : Client(input_ip, port, server_ip, server_port){
            listen = new ClientListener(this);
         }

         /**
         * Starts the read thread
         */
        void waitForConnectionsAndRead() {
            listen->start();
        }
};