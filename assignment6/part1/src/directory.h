#pragma once

#include "array.h"
#include "object.h"
#include "string.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * Class that keeps track of ips and the sockets opens connecting to
 * these ips.
 * */
class Directory : Object {
    public: 
        // Maps a string to a Int Wrapper containing a socket
        Map* ip_to_sock;
        char* this_ip;
        int this_port;

        Directory() {
            ip_to_sock = new Map();
        }

        Directory(char* dir) {

            StrBuff s;
            
            for (int x = 0; dir[x] != '\0'; x++) {
                if (dir[x] == '|') {
                    // ADD MAP TO INT
                    ip_to_sock->set(s.get(), new IntObj(-1));
                }
                else {
                    s.c(dir[x]);
                }
            }
        }

        char* c_str() {
            StrBuff s;
            s.c("DIRECTORY-");
            String ** keys = ip_to_sock->keys();
            for (int x = 0; x < ip_to_sock->size(); x++) {
                s.c(keys[x]->c_str());
                s.c("|");
            }

            return s.get()->c_str();
        }

        void checkAddDir(char* dir) {
            checkAddDir(dir, -1);
        }

        void checkAddDir(char* dir, int sock) {
            StrBuff s;
            s.p("ADDDING TO DIRECTIORY : ");
            s.p(dir);
            s.p("\n");
            
            int beg = 0;
            for (int x = 0; dir[x] != '\0'; x++) {
                if (dir[x] == '|') {
                    char* d = new char[32];
                    sprintf(d, "%.*s", x - beg, dir); 
                    String* str = new String(d);
                    s.p("THIS IS THE STRING : ");
                    s.p(str->c_str());
                    s.p("\n");
                    if (!(ip_to_sock->has(str)))
                    {
                        ip_to_sock->set(str, new IntObj(sock));
                    }
                    beg = x + 1;
                }
            }
        }

        size_t getSize() {
            return ip_to_sock->size();
        }

        void remove(char* ip) {
            return ip_to_sock->remove(new String(ip));
        }

        IntArray* getSockets() {
            IntArray* returning = new IntArray();
            String** keys = ip_to_sock->keys();
            for (int x = 0; x < getSize(); x++) {
                IntObj* iobj = dynamic_cast <IntObj*> (ip_to_sock->get(keys[x]));
                if (iobj->getInt() != -1) {
                    returning->add(iobj->getInt());
                }
            }
            return returning;

        }

        int getSockForIp(char* ip) {
            IntObj* intobj =  dynamic_cast<IntObj*> (ip_to_sock->get(new String(ip)));
            int n =  intobj->getInt();
            if (n == -1) {
                StrBuff s;
                int connecting_port;
                char* connecting_ip; 

                for (int x = 0; ip[x] != '\0'; x++) {
                    if (ip[x] == '|') {
                        connecting_port = atoi(s.get()->c_str());
                    }
                    if (ip[x] == ':') {
                        connecting_ip = s.get()->c_str();
                    }
                    else {
                        s.c(ip[x]);
                    }
                }
                
                struct sockaddr_in connecting;
                assert((n = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
                connecting.sin_family = AF_INET;
                connecting.sin_port = htons(this_port);
                assert(inet_pton(AF_INET, this_ip, &connecting.sin_addr)>0);
                assert(bind(n, (struct sockaddr *)&connecting, sizeof(connecting))>=0);

                connecting.sin_family = AF_INET;
                connecting.sin_port = htons(connecting_port);
                // Convert IP addresses from text to binary form
                assert(inet_pton(AF_INET, connecting_ip, &connecting.sin_addr)>0);
                assert(connect(n, (struct sockaddr *)&connecting, sizeof(connecting)) >= 0);
                ip_to_sock->set(new String(ip), new IntObj(n));
            }
            return n;
        }
};