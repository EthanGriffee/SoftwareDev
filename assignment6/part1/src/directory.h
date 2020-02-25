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

class Directory : Object {
    public: 
        // String to int wrapper
        StringArray* str_arr;

        Directory() {
            str_arr = new StringArray();
        }

        Directory(char* dir) {

            StrBuff s;
            
            for (int x = 0; dir[x] != '\0'; x++) {
                if (dir[x] == '|') {
                    // ADD MAP TO INT
                    str_arr->add(s.get());
                }
                else {
                    s.c(dir[x]);
                }
            }
        }

        char* c_str() {
            StrBuff s;
            s.c("DIRECTORY-");
            s.p(str_arr->getSize());

            for (int x = 0; x < str_arr->getSize(); x++) {
                s.c(str_arr->get(x)->c_str());
                s.c("|");
            }

            return s.get()->c_str();
        }

        void checkAddDir(char* dir) {
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
                    if (str_arr->indexOf(str) == -1)
                    {
                        str_arr->add(str);
                    }
                    beg = x + 1;
                }
            }

        }
};