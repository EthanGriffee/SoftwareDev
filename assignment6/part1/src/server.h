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

class Server : public Object {
    public:
        Map* ips_to_ints;
        IntArray* sockets;
        StringArray* ips;
        int server_fd;
        int port = 8518;
        sockaddr_in serv;
        Lock l;
        

        Server(char* input_ip, int input_port) {
            int opt=1;
            port = input_port;
            ips_to_ints = new Map();
            sockets = new IntArray();
            assert((server_fd = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            assert(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            //serv.sin_addr.s_addr = INADDR_ANY;
            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, input_ip, &serv.sin_addr)>0);
            assert(bind(server_fd, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            assert(listen(server_fd, 10) >= 0);
        }

        void broadCastToAll(char* message) {
            for (int x = 0; x < sockets->getSize(); x++) {
                send(sockets->get(x) , message, strlen(message) , 0 );
            }

        }

        void sendMessage(char* ip, char* message) {
            send(sockets->get(sockets->get(ips->indexOf(new String(ip)))) , message, strlen(message) , 0 );
        }

        virtual void closeSocket() {
            close(server_fd);
        }

};

class ServerReadListener : public Thread {
    public:
        Server* s;

        ServerReadListener(Server* s) {
            this->s = s;
        }

        // from https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
        virtual void run() {
            char buffer[1024];
            fd_set readfds;
            int valread;
            while(true) {
                //clear the socket set  
                FD_ZERO(&readfds);
                int addrlen = sizeof(s->serv);
                int max_clients = s->sockets->getSize();
            
                //add master socket to set  
                FD_SET(s->server_fd, &readfds);   
                int max_sd = s->server_fd;   
                    
                //add child sockets to set  
                for ( int i = 0; i < max_clients; i++)   
                {   
                    //socket descriptor  
                    int sd = s->sockets->get(i);   
                        
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
                    printf("server shutting down");
                    return; 
                }   
                    
                //If something happened on the master socket ,  
                //then its an incoming connection  
                if (FD_ISSET(s->server_fd, &readfds))   
                {   
                    int new_socket;
                    assert((new_socket = accept(s->server_fd, (struct sockaddr *)&s->serv, (socklen_t*)&addrlen)) >= 0);
                    s->sockets->add(new_socket);
                    char* count = new char[32];
                    StrBuff message;
                    message.p("TEST : ");
                    message.p(getsockname(new_socket, (struct sockaddr*)&s->serv, (socklen_t*)&addrlen));
                    message.p("\n");
                    sprintf(count, "%i", getsockname(new_socket, (struct sockaddr*)&s->serv, (socklen_t*)&addrlen)); 
                    message = message.c("WELCOME New Client Number ");
                    message = message.c(count);
                    s->broadCastToAll(message.get()->c_str());
                    
                    //inform user of socket number - used in send and receive commands  
                    printf("New connection , socket fd is %d , ip is : %s , port : %d  \n" , new_socket , inet_ntoa(s->serv.sin_addr) , ntohs (s->serv.sin_port));   
                
                        
                    puts("Welcome message sent successfully");
                }


                for (int i = 0; i < s->sockets->getSize(); i++)   
                {   
                    int sd = s->sockets->get(i); 
                        
                    if (FD_ISSET( sd , &readfds))   
                    {   
                        //Check if it was for closing , and also read the  
                        //incoming message  
                        if ((valread = (read( sd , buffer, 1024))) == 0)   
                        {   
                            //Somebody disconnected , get his details and print  
                            getpeername(sd , (struct sockaddr*)&s->serv, (socklen_t*)&addrlen);   
                            printf("Host disconnected , ip %s , port %d \n", inet_ntoa(s->serv.sin_addr) , ntohs(s->serv.sin_port));   
                                
                            //Close the socket and mark as 0 in list for reuse  
                            close( sd );   
                            s->sockets->remove(i); 
                        }   
                            
                        //Echo back the message that came in  
                        else 
                        {   
                            //set the string terminating NULL byte on the end  
                            //of the data read  
                            printf("READ A MESSAGE");
                            buffer[valread] = '\0';   
                            send(sd , buffer , strlen(buffer) , 0 );
                            printf("Server recieved message : ");
                            StrBuff ip, mess;
                            ip.p(buffer);
                            ip.p("\n");
                            int x = 3;
                            if (buffer[0] == 'T') {
                                while (buffer[x] != '|') {
                                    ip.c(buffer[x]);
                                    x += 1;
                                }
                                x += 1;
                                while(buffer[x] != '\0') {
                                    mess.c(buffer[x]);
                                    x += 1;
                                }
                                printf("IP IS : ");
                                mess.p(ip.get());
                                printf(" message is : ");
                                ip.p(mess.get());
                                printf("\n");
                                //s->sendMessage(ip.get()->c_str(), mess.get()->c_str());
                            }
                        }   
                    }   
                } 
            }  
        }
};