#include "map.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

class Network : public Object {
    public:

        Map* userToIp;
        int server_fd, sock;
        

        Network() {
            userToIp = new Map();
            struct sockaddr_in serv;
            char *hello = "Hello from client";
            char buffer[1024] = {0};
            assert((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(PORT);
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, "127.0.0.1",&serv.sin_addr)>0);
            assert(connect(sock,
        (struct sockaddr *)&serv,
        sizeof(serv)) >= 0);
            printf("Hello message sent\n");
            int valread = read( sock , buffer, 1024);
            printf("%s\n",buffer );
        }

        void waitForMessage() {
            char buffer[1024];
            while (true) {
                int valread = read(sock, buffer, 1024);
            }
        }

        void broadCastToAll(char* message) {
            for (int x = 0; x < ; x++) {
                send(sock , message, strlen(message) , 0 );
            }

        }

        void sendMesage(String username, String message) {

        }

};

class Client : public Object {
    public:
        int server_fd;

        Client() {

        }
}