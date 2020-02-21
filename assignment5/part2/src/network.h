#include "array.h"
#include "object.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

class Server : public Object {
    public:

        IntArray* sockets;
        int sock;
        int PORT = 9002;
        

        Server(char* input_ip) {
            sockets = new IntArray();
            struct sockaddr_in serv;
            assert((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(PORT);
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, input_ip,&serv.sin_addr)>0);
            assert(bind(sock, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
        }

        void waitForConnections() {
            char buffer[1024];
            while (true) {
                int new_socket;
                listen(sock, 10);
                new_socket = accept(sock, NULL, NULL);
                int valread = read(sock, buffer, 1024);
                broadCastToAll("New Client has joined");
                printf("Hello message recieved\n");
            }
        }

        void broadCastToAll(char* message) {
            for (int x = 0; x < sockets->getSize(); x++) {
                send(sockets->get(x) , message, strlen(message) , 0 );
            }

        }

        void sendMesage(size_t num, char* message) {
            send(sockets->get(num) , message, strlen(message) , 0 );
        }

        void closeSocket() {
            close(sock);
        }

};

class Client : public Object {
    public:
        int sock;
        const char* SERVER_IP = "127.0.0.1";
        int SERVER_PORT = 9002;

        Client(char* ip) {
            struct sockaddr_in serv;
            char *hello = "Hello from client";
            assert((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(9002);
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, SERVER_IP,&serv.sin_addr)>0);
            assert(connect(sock, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            printf("Hello message sent\n");
        }


        void waitForMessage() {
            char buffer[1024];
            while (true) {
                assert(recv(sock, buffer, 1024, 0) >= 0);

                printf("recieved message: %s", buffer);
            }
        }

        void closeSocket() {
            close(sock);
        }
};