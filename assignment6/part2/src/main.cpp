#pragma once

#include "string.h"
#include "object.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class StringArray {
   String* vals_;

};

 

class DoubleArray {
  double* vals_;

};

 

enum class MsgKind { Ack, Nack, Put,
                    Reply,  Get, WaitAndGet, Status,
                    Kill,   Register,  Directory };

 

class Message : public Object {
    public: 
        MsgKind kind_;  // the message kind
        size_t sender_; // the index of the sender node
        size_t target_; // the index of the receiver node
        size_t id_;     // an id t unique within the node

        Message(size_t sender_, size_t target_, size_t id_) {
            this->sender_ = sender_;
            this->target_ = target_;
            this->id_ = id_;
        }

};

 

class Ack : public Message {
    public:

        Ack(size_t sender_, size_t target_, size_t id_) :  Message(sender_, target_, id_) {
            kind_ = MsgKind::Ack;
        }

};

 

class Status : public Message {
    public:
        String* msg_; // owned

        Status(String* msg_, size_t sender_, size_t target_, size_t id_) :  Message(sender_, target_, id_) {
            kind_ = MsgKind::Status;
            this->msg_ = msg_;
        }


};

 

class Register : public Message {
    public:
        sockaddr_in slave;
        size_t port;

        Register(sockaddr_in slave, size_t port, size_t sender_, size_t target_, size_t id_) :  Message(sender_, target_, id_) {
            kind_ = MsgKind::Register;
            this->port = port;
            this->slave = slave;
        }

};

 

class Directory : public Message {
    public:
        size_t slaves;
        size_t * ports;  // owned
        String ** addresses;  // owned; strings owned

        Directory(size_t slaves, size_t* ports, String** addresses, size_t sender_, size_t target_, size_t id_) :  Message(sender_, target_, id_) {
            kind_ = MsgKind::Directory;
            this->ports = ports;
            this->slaves = slaves;
            this->addresses = addresses;
        }

};

