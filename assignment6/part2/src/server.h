#pragma once

#include "array.h"
#include "object.h"
#include "deserialize_message.h"
#include "message.h"
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

class Server : public Object {
    public:
        Directory dir;
        int server_fd;
        int port = 8518;
        sockaddr_in serv;
        Lock l;
        

        Server(char* input_ip, int input_port) {
            int opt=1;
            port = input_port;
            assert((server_fd = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
            assert(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);

            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, input_ip, &serv.sin_addr)>0);
            assert(bind(server_fd, (struct sockaddr *)&serv, sizeof(serv)) >= 0);
            assert(listen(server_fd, 10) >= 0);
        }

        void broadCastToAll(char* message) {
            IntArray* sockets = dir.getSockets();
            for (int x = 0; x < dir.getSize(); x++) {
                send(sockets->get(x) , message, strlen(message) , 0 );
            }

        }

        void sendMessage(char* ip, char* message) {
            send(dir.getSockForIp(ip) , message, strlen(message) , 0 );
        }

        virtual void closeSocket() {
            close(server_fd);
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
                FD_SET(server_fd, &readfds);   
                int max_sd = server_fd;  

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
                    printf("server shutting down");
                    return; 
                }   
                    
                //If something happened on the master socket ,  
                //then its an incoming connection  
                if (FD_ISSET(server_fd, &readfds))   
                {   
                    int new_socket;
                    sockaddr_in addr;
                    int addrlen = sizeof(addr);
                    assert((new_socket = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) >= 0);
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
                                case(MsgKind::Register): {
                                    sockaddr_in addr = m->asReg()->getSockAddr();
                                    char* count = new char[32];
                                    sprintf(count, "%s:%d|", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); 
                                    dir.checkAddDir(new String(count), sd);
                                    broadCastToAll(new Dir(dir, 1, 2)->serialize());
                                }
                                case(MsgKind::Dir): {
                                    // proccessses dir
                                }
                                case(MsgKind::Status): {
                                    // proccessses Status
                                }
                            }
                        }   
                    }   
                } 
            }  
            
        }

};

class ServerReadListener : public Thread {
    public:
        Server* s;

        ServerReadListener(Server* s) {
            this->s = s;
        }

        // runs the accept and read messages indefinetly
        virtual void run() {
            s->acceptAndReadMessages();
        }
};