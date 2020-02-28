#pragma once

#include "array.h"
#include "object.h"
#include "string.h"
#include "map.h"
#include "message.h"
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
        IntArray* sockets_without_ips;
        char* this_ip;
        int this_port;

        Directory() {
            ip_to_sock = new Map();
            sockets_without_ips = new IntArray();
        }

        Directory(StringArray* dir) {
            ip_to_sock = new Map();
            sockets_without_ips = new IntArray();

            for (int x = dir->getSize() - 1; x >= 0; x--) {
                ip_to_sock->set(dir->get(x), new IntObj(-1));
            }
        }

        void checkAddDir(StringArray* ips) {
            for(int x = 0; x < ips->getSize(); x++) {
                checkAddDir(ips->get(x));
            }
        }

        void putSocketWithoutIp(int sock) {
            sockets_without_ips->add(sock);
        }

        void checkAddDir(String* ip) {
            checkAddDir(ip, -1);
        }

        void checkAddDir(String* ip, int sock) {
            StrBuff s;
            if (!(ip_to_sock->has(ip)))
            {
                ip_to_sock->set(ip, new IntObj(sock));
                int index = sockets_without_ips->indexOf(sock);
                if (index != -1) {
                    sockets_without_ips->remove(index);
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
            returning->addAll(sockets_without_ips);
            return returning;
        }

        StringArray* getIps() {
            StringArray* returning = new StringArray();
            String** keys = ip_to_sock->keys();
            for (int x = 0; x < getSize(); x++) {
                returning->add(keys[x]);
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