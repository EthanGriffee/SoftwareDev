#pragma once

#include "string.h"
#include "object.h"
#include "helper.h"
#include "serial.h"
#include "assert.h"
#include "array.h"
#include "directory.h"
#include "deserialize_string_array.h"
#include "deserialize.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Ack;
class Dir;
class Status;
class Register;
class Exit;

enum class MsgKind { Ack, Nack, Put,
                    Reply,  Get, WaitAndGet, Status,
                    Exit,   Register,  Dir };

 

class Message : public Object {
    public: 
        MsgKind kind_;  // the message kind
        size_t sender_; // the index of the sender node
        size_t target_; // the index of the receiver node

        Message() {}

        Message(size_t sender_, size_t target_) {
            this->sender_ = sender_;
            this->target_ = target_;
        }

        size_t getSender() {
            return sender_;
        }

        size_t getTarget() {
            return target_;
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
                case(MsgKind::Dir): {
                    return "Dir";
                }
                case(MsgKind::Status): {
                    return "Status";
                }
            }
            assert(-1);
        }

        /**
         * returns a char* representation of the Object.
         * */
        virtual char* serialize() {
            char* buff = new char[2048];
            sprintf(buff, "{MESSAGE|kind_=%s|sender_=%02x|target_=%02x|%s", msgKindAsChar(), sender_, target_, this->serializeAditionalFields_()); 
            return buff;
        }

        virtual char* serializeAditionalFields_() {
            return "}";
        }

        virtual bool equals(Object* other) {
            Message* m = dynamic_cast<Message*> (other);
            if(m) {
                return this->kind_ == m->getKind() && this->sender_ == m->getSender() && this->target_ == m->getTarget();
            }
            else {
                return false;
            }
        }

        virtual Ack* asAck() {
            return nullptr;
        }

        virtual Register* asReg() {
            return nullptr;
        }

        virtual Status* asStatus() {
            return nullptr;
        }

        virtual Dir* asDir() {
            return nullptr;
        }
                
        virtual Exit* asExit() {
            return nullptr;
        }
};

 

class Ack : public Message {
    public:

        Ack(size_t sender_, size_t target_) :  Message(sender_, target_) {
            kind_ = MsgKind::Ack;
        }

        Ack(char* ack) {
            kind_ = MsgKind::Ack;
            int x = 19;
            int y;
            assert(strcmp(this->substring(ack, 0, x), "{MESSAGE|kind_=Ack|") == 0);
            assert(strcmp(this->substring(ack, x, 8), "sender_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(ack, x);
            char* c = this->substring(ack, x, y);
            this->sender_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(this->substring(ack, x, 8), "target_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(ack, x);
            c = this->substring(ack, x, y);
            this->target_ = strtol(c, nullptr, 10);
        }

        virtual Ack* asAck() {
            return this;
        }
};

 

class Status : public Message {
    public:
        String* msg_; // owned

        Status(String* msg_, size_t sender_, size_t target_) :  Message(sender_, target_) {
            kind_ = MsgKind::Status;
            this->msg_ = msg_;
        }

        Status(char* status) {
            kind_ = MsgKind::Status;
            int x = 22;
            int y;
            assert(strcmp(substring(status, 0, x), "{MESSAGE|kind_=Status|") == 0);
            assert(strcmp(substring(status, x, 8), "sender_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(status, x);
            char* c = this->substring(status, x, y);
            this->sender_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(status, x, 8), "target_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(status, x);
            c = this->substring(status, x, y);
            this->target_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(status, x, 5), "msg_=") == 0);
            x = x + 5;
            y = this->parseUntilClassSeperator(status, x);
            c = this->substring(status, x, y);
            StringDeserializer sd;
            this->msg_ = sd.deserialize(c);
        }

        String* getMessage() {
            return msg_;
        }


        virtual char* serializeAditionalFields_() {
            char* buff = new char[2048];
            sprintf(buff, "msg_=%s|}", msg_->serialize()); 
            return buff;
        }
        
        virtual bool equals(Object* other) {
            Status* a = dynamic_cast<Status*> (other);
            if(a) {
                return this->kind_ == a->getKind() && this->sender_ == a->getSender() && this->target_ == a->getTarget() && a->getMessage()->equals(this->getMessage());
            }
            else {
                return false;
            }
        }

        virtual Status* asStatus() {
            return this;
        }
};

 

class Register : public Message {
    public:
        sockaddr_in client;

        Register(sockaddr_in client, size_t sender_, size_t target_) :  Message(sender_, target_) {
            kind_ = MsgKind::Register;
            this->client = client;
        }

        Register(char* reg) {
            kind_ = MsgKind::Register;
            int x = 24;
            int y;
            assert(strcmp(substring(reg, 0, x), "{MESSAGE|kind_=Register|") == 0);
            assert(strcmp(substring(reg, x, 8), "sender_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(reg, x);
            char* c = this->substring(reg, x, y);
            this->sender_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(reg, x, 8), "target_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(reg, x);
            c = this->substring(reg, x, y);
            this->target_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(reg, x, 13), "client=[port=") == 0);
            x = x + 13;
            y = this->parseUntilSeperator(reg, x);
            c = this->substring(reg, x, y);
            x = x + y + 1;
            client.sin_family = AF_INET;
            client.sin_port = htons(strtol(c, nullptr, 10));
            assert(strcmp(substring(reg, x, 3), "ip=") == 0);
            x = x + 3;
            y = this->parseUntilBracketSeperator(reg, x);
            c = this->substring(reg, x, y);

            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, c, &client.sin_addr)>0);


        }

        virtual Register* asReg() {
            return this;
        }

        virtual sockaddr_in getSockAddr() {
            return client;
        } 

        virtual char* serializeAditionalFields_() {
            char* buff = new char[2048];
            sprintf(buff, "client=[port=%d|ip=%s]|}", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
            return buff;

        }

        virtual bool equals(Object* other) {
            Register* m = dynamic_cast<Register*> (other);
            if(m) {
                return this->kind_ == m->getKind() && this->sender_ == m->getSender() && this->target_ == m->getTarget();
            }
            else {
                return false;
            }
        }
};

class Dir : public Message {
    public:
        StringArray* ips_;

        Dir(Directory d, size_t sender_, size_t target_) :  Message(sender_, target_) {
            kind_ = MsgKind::Dir;
            ips_ = d.getIps();
        }

        Dir(char* dir) {
            kind_ = MsgKind::Dir;
            int x = 19;
            int y;
            assert(strcmp(substring(dir, 0, x), "{MESSAGE|kind_=Dir|") == 0);
            assert(strcmp(substring(dir, x, 8), "sender_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(dir, x);
            char* c = this->substring(dir, x, y);
            this->sender_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(dir, x, 8), "target_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(dir, x);
            c = this->substring(dir, x, y);
            this->target_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(dir, x, 5), "ips_=") == 0);
            x = x + 5;
            y = this->parseUntilClassSeperator(dir, x);
            c = this->substring(dir, x, y);
            StringArrayDeserializer sad;
            this->ips_ = sad.deserialize(c);
            
        }

        virtual char* serializeAditionalFields_() {
            char* buff = new char[2048];
            sprintf(buff, "ips_=%s|}", ips_->serialize()); 
            return buff;
        }

        StringArray* getIps() {
            return ips_;
        }

        virtual bool equals(Object* other) {

            Dir* m = dynamic_cast<Dir*> (other);
            if(m) {
                return this->kind_ == m->getKind() && this->sender_ == m->getSender() && this->target_ == m->getTarget() && this->ips_->equals(m->getIps());
            }
            else {
                return false;
            }
        }

        virtual Dir* asDir() {
            return this;
        }
};

class Exit : public Message {
    public:
        sockaddr_in client;

        Exit(sockaddr_in client, size_t sender_, size_t target_) :  Message(sender_, target_) {
            kind_ = MsgKind::Exit;
            this->client = client;
        }

        Exit(char* reg) {
            kind_ = MsgKind::Exit;
            int x = 20;
            int y;
            assert(strcmp(substring(reg, 0, x), "{MESSAGE|kind_=Exit|") == 0);
            assert(strcmp(substring(reg, x, 8), "sender_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(reg, x);
            char* c = this->substring(reg, x, y);
            this->sender_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(reg, x, 8), "target_=") == 0);
            x = x + 8;
            y = this->parseUntilSeperator(reg, x);
            c = this->substring(reg, x, y);
            this->target_ = strtol(c, nullptr, 10);
            x = x + y;
            x = x + 1;
            assert(strcmp(substring(reg, x, 13), "client=[port=") == 0);
            x = x + 13;
            y = this->parseUntilSeperator(reg, x);
            c = this->substring(reg, x, y);
            x = x + y + 1;
            client.sin_family = AF_INET;
            client.sin_port = htons(strtol(c, nullptr, 10));
            assert(strcmp(substring(reg, x, 3), "ip=") == 0);
            x = x + 3;
            y = this->parseUntilBracketSeperator(reg, x);
            c = this->substring(reg, x, y);

            // Convert IP addresses from text to binary form
            assert(inet_pton(AF_INET, c, &client.sin_addr)>0);


        }

        virtual Exit* asExit() {
            return this;
        }

        virtual sockaddr_in getSockAddr() {
            return client;
        } 

        virtual char* serializeAditionalFields_() {
            char* buff = new char[2048];
            sprintf(buff, "client=[port=%d|ip=%s]|}", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
            return buff;

        }

        virtual bool equals(Object* other) {
            Register* m = dynamic_cast<Register*> (other);
            if(m) {
                return this->kind_ == m->getKind() && this->sender_ == m->getSender() && this->target_ == m->getTarget();
            }
            else {
                return false;
            }
        }
};