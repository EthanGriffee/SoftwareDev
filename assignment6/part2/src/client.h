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
#include "deserialize_message.h"
#include "directory.h"

class Client : public Object {
    public:
        int server_sock;
        int listening_sock;
        char* ip;
        char* server_ip;
        int port;
        int server_port;
        sockaddr_in listening_addr;
        Directory dir;

        Client(char* ip, int input_port, char* server_ip, int server_port) {
            int opt=1;
            port = input_port;
            assert((listening_sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            assert(setsockopt(listening_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0);
            listening_addr.sin_family = AF_INET;
            listening_addr.sin_port = htons(port);

            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, ip, &listening_addr.sin_addr)>0);
            assert(bind(listening_sock, (struct sockaddr *)&listening_addr, sizeof(listening_addr)) >= 0);
            assert(listen(listening_sock, 10) >= 0);

            this->ip = ip;
            this->server_ip = server_ip;
            struct sockaddr_in serv;
            assert((server_sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            assert(inet_pton(AF_INET, ip, &serv.sin_addr)>0);
            assert(bind(server_sock, (struct sockaddr *)&serv, sizeof(serv))>=0);

            serv.sin_family = AF_INET;
            serv.sin_port = htons(server_port);
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, server_ip, &serv.sin_addr)>0);
            assert(connect(server_sock, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            char* sending = new Register(listening_addr, 1, 1)->serialize();
            send(server_sock, sending , strlen(sending) , 0 );
        }

        virtual void sendMessage(char* ip, const char* message) {
            printf("SENDING : %s\n", message);
            send(dir.getSockForIp(ip) , message, strlen(message) , 0 );
        }

        virtual void closeSocket() {
            close(server_sock);
        }

        void acceptAndReadMessages() {
            char buffer[1024];
            fd_set readfds;
            int valread;
            while(true) {
                //clear the socket set  
                FD_ZERO(&readfds);
                int max_clients = dir.getSize();
            
                //add master socket to set  
                FD_SET(listening_sock, &readfds);   
                int max_sd = listening_sock;  

                IntArray* sockets = dir.getSockets(); 
                    
                //add child sockets to set  
                for ( int i = 0; i < max_clients; i++)   
                {   
                    //socket descriptor  
                    int sd = sockets->get(i);   
                        
                    //if valid socket descriptor then add to read list  
                    if(sd > 0)   
                        FD_SET( sd , &readfds);   
                        
                    //highest file descriptor number, need it for the select function  
                    if(sd > max_sd)   
                        max_sd = sd;   
                }   
            
                //wait for an activity on one of the sockets , timeout is NULL ,  
                //so wait indefinitely  
                int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
            
                if ((activity < 0) && (errno!=EINTR))   
                {   
                    printf("client exiting");
                    return; 
                }   
                    
                //If something happened on the master socket ,  
                //then its an incoming connection  
                if (FD_ISSET(listening_sock, &readfds))   
                {   
                    int new_socket;
                    sockaddr_in addr;
                    int addrlen = sizeof(addr);
                    assert((new_socket = accept(listening_sock, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) >= 0);
                    char* count = new char[32];
                    sprintf(count, "%s:%d|", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); 
                    dir.putSocketWithoutIp(new_socket);
                }


                for (int i = 0; i < max_clients; i++)   
                {   
                    int sd = sockets->get(i); 
                        
                    if (FD_ISSET( sd , &readfds))   
                    {   
                        //Check if it was for closing , and also read the  
                        //incoming message  
                        if ((valread = (read( sd , buffer, 1024))) == 0)   
                        {   
                            sockaddr_in addr;
                            int addrlen = sizeof(addr);
                            //Somebody disconnected , get his details and print  
                            getpeername(sd , (struct sockaddr*)&addr, (socklen_t*)&addrlen);   
                            printf("Host disconnected , ip %s , port %d \n", inet_ntoa(addr.sin_addr) , ntohs(addr.sin_port));   
                            char* count = new char[32];
                            sprintf(count, "%s:%d|", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); 
                            //Close the socket and mark as 0 in list for reuse  
                            close( sd );   
                            dir.remove(count); 
                        }   
                            
                        //Echo back the message that came in  
                        else 
                        {   
                            //set the string terminating NULL byte on the end  
                            //of the data read  
                            this->p("\n recieved message - ");
                            this->p(buffer);
                            MessageDeserializer md;

                            Message* m = md.deserialize(buffer);
                            switch(m->getKind()) {
                                case(MsgKind::Ack): {
                                    // do nothing as we don't handle ACKS
                                }
                                case(MsgKind::Nack): {
                                    //sends the previous message again.
                                    
                                }
                                case(MsgKind::Dir): {
                                    dir.checkAddDir(m->asDir()->getIps());
                                }
                                case(MsgKind::Status): {
                                    printf("%s:%i | RECIEVED MESSAGE - %s", ip, port, m->asStatus()->getMessage());
                                    // proccessses Status
                                }
                            }
                        }   
                    }   
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
            c->acceptAndReadMessages();
        }
};