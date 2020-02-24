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
class Server : public Object {
    public:

        IntArray* sockets;
        StringArray* ips;
        int sock;
        int PORT = 8303;
        Lock l;
        

        Server(char* input_ip) {
            int opt=1;
            sockets = new IntArray();
            struct sockaddr_in serv;
            assert((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            assert(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(PORT);
            //serv.sin_addr.s_addr = INADDR_ANY;
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, input_ip,&serv.sin_addr)>0);
            assert(bind(sock, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            listen(sock, 10);
        }

        void broadCastToAll(char* message) {
            Sys s;
            s.p(sockets->getSize());
            for (int x = 0; x < sockets->getSize(); x++) {
                send(sockets->get(x) , message, strlen(message) , 0 );
            }

        }

        void sendMessage(char* ip, char* message) {
            send(sockets->get(sockets->get(ips->indexOf(new String(ip)))) , message, strlen(message) , 0 );
        }

        virtual void closeSocket() {
            close(sock);
        }

};

class Client : public Object {
    public:
        int sock;
        const char* SERVER_IP = "127.0.0.1";
        int SERVER_PORT = 8303;

        Client(char* ip) {
            struct sockaddr_in serv;
            assert((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(SERVER_PORT);

            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, SERVER_IP,&serv.sin_addr)>0);
            assert(connect(sock, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            send(sock, ip , strlen(ip) , 0 );
        }

        virtual void composeMessage(const char* ip, const char* message) {
            StrBuff sending;
            sending = sending.c("TO: ");
            sending = sending.c(ip);
            sending = sending.c("|");
            sending = sending.c(message);
            sendMessage(sending.get()->c_str());
        }

        void sendMessage(const char* message) {
            printf("SENDING : %s\n", message);
            send(sock , message, strlen(message) , 0 );
        }

        virtual void closeSocket() {
            close(sock);
        }
};

class ServerConnectListener : public Thread {
    public:
        Server* s;

        ServerConnectListener() {}

        ServerConnectListener(Server* s) {
            this->s = s;
        }

        virtual void run() {
            char buffer[1024];
            struct sockaddr_in adr;
            adr.sin_family = AF_INET;
            adr.sin_addr.s_addr = INADDR_ANY;
            int addrlen = sizeof(adr);
            int new_socket;
            while((new_socket = accept(s->sock, (struct sockaddr*)&adr, (socklen_t*)&addrlen))>=0) {
                s->sockets->add(new_socket);
                char* count = new char[32];
                StrBuff message;
                sprintf(count, "%zu", s->sockets->getSize()); 
                message = message.c("WELCOME New Client Number ");
                message = message.c(count);
                s->broadCastToAll(message.get()->c_str());
            }
        }
};

class ServerReadListener : public Thread {
    public:
        Server* s;

        ServerReadListener(Server* s) {
            this->s = s;
        }

        virtual void run() {
            char buffer[1024];
            while(read(s->sock, buffer, 1024) >= 0) {
                printf("Server recieved message");
                StrBuff ip, mess;
                int x = 3;
                if (buffer[x] == 'T') {
                    x = 3;
                    while (buffer[x] != '|') {
                        ip.c(buffer[x]);
                        x += 1;
                    }
                    x += 1;
                    while(buffer[x] != '\0') {
                        mess.c(buffer[x]);
                        x += 1;
                    }
                    s->sendMessage(ip.get()->c_str(), mess.get()->c_str());
                }
                else {
                    while (buffer[x] != '\0') {
                        ip.c(buffer[x]);
                        x += 1;
                    }
                    s->ips->add(ip.get());
                }
            }  
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
            while (read(c->sock, buffer, 1024) >= 0 ) {
                printf("recieved message: %s\n", buffer);
            }
        }
};

class ThreadedServer : public Server {
    public:
        ServerConnectListener* conn;
        ServerReadListener* read;

        ThreadedServer(char* input_ip) : Server(input_ip){
            conn = new ServerConnectListener(this);
            read = new ServerReadListener(this);

        }

        void waitForConnectionsAndRead() {
            conn->start();
            read->start();
        }
};

class ThreadedClient : public Client {
    public:
        ClientListener* listen;

        ThreadedClient(char* input_ip) : Client(input_ip){
            listen = new ClientListener(this);
         }

        void readMessages() {
            listen->start();
        }
};