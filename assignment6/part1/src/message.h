#pragma once

#include "string.h"
#include "object.h"
#include "serialize.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


enum class MsgKind { Ack, Nack, Put,
                    Reply,  Get, WaitAndGet, Status,
                    Kill,   Register,  Dir };

class Dir;
class Status;
class StringColumn;
class IntColumn;

 

class Message : public Object, Serialize {
    public: 
        MsgKind kind_;  // the message kind
        size_t sender_; // the index of the sender node
        size_t target_; // the index of the receiver node

        Message(size_t sender_, size_t target_) {
            this->sender_ = sender_;
            this->target_ = target_;
        }

        MsgKind getKind() {
            return kind_;
        }

        char* msgKindAsChar() {
            switch(kind_) {
                case(MsgKind::Ack): {
                    return "Ack";
                }
                case(MsgKind::Nack): {
                    return "Nack";
                }
                case(MsgKind::Register): {
                    return "Register";
                }
                case(MsgKind::Directory): {
                    return "Directory";
                }
            }
        }

        /**
         * returns a char* representation of the Object.
         * */
        virtual char* serialize() {
            char* buff = new char[1024];
            sprintf(buff, "MESSAGE{kind_=%s|sender_=%t|target=%t}", msgKindAsChar(), sender_, target_); 
            return buff;

        }
};

 

class Ack : public Message {
    public:

        Ack(size_t sender_, size_t target_, size_t id_) :  Message(sender_, target_) {
            kind_ = MsgKind::Ack;
        }

};

 

class Status : public Message {
    public:
        String* msg_; // owned

        Status(String* msg_, size_t sender_, size_t target_, size_t id_) :  Message(sender_, target_) {
            kind_ = MsgKind::Status;
            this->msg_ = msg_;
        }

        String* getMessage() {
            return msg_;
        }


};

 

class Register : public Message {
    public:
        sockaddr_in slave;
        size_t port;

        Register(sockaddr_in slave, size_t port, size_t sender_, size_t target_) :  Message(sender_, target_) {
            kind_ = MsgKind::Register;
            this->port = port;
            this->slave = slave;
        }

};