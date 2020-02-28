#pragma once

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
#include "thread.h"
#include "map.h"
#include "directory.h"

class Client : public Object {
    public:
        int sock;
        char* ip;
        char* server_ip;
        int port;
        int server_port;
        Directory d;

        Client(char* ip, int input_port, char* server_ip, int server_port) {
            port = input_port;
            this->ip = ip;
            this->server_ip = server_ip;
            struct sockaddr_in serv;
            assert((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            assert(inet_pton(AF_INET, ip, &serv.sin_addr)>0);
            assert(bind(sock, (struct sockaddr *)&serv, sizeof(serv))>=0);

            serv.sin_family = AF_INET;
            serv.sin_port = htons(server_port);
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, server_ip, &serv.sin_addr)>0);
            assert(connect(sock, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            send(sock, "SIGN UP" , strlen(ip) , 0 );
        }

        virtual void composeMessage(const char* ip, const char* message) {
            StrBuff sending;
            sending = sending.c("TO: ");
            sending = sending.c(ip);
            sending = sending.c("|");
            sending = sending.c(message);
            sendMessage(sending.get()->c_str());
        }

        void sendMessage(char* message) {
            printf("SENDING : %s\n", message);
            send(sock , message, strlen(message) , 0 );
        }

        virtual void closeSocket() {
            close(sock);
        }
};

class ClientListener : public Thread {
    public:
        Client* c;

        ClientListener(Client* c) {
            this->c = c;
        }

        virtual void run() {
            char buffer[1024];
            while (read(c->sock, buffer, 1024) >= 0) {
                printf("IP: %s:%i | recieved message: %s\n", c->ip, c->port, buffer);
            }
            printf("%s will stop reading\n", c->ip);
        }
};