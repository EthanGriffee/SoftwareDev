#pragma once

#include <string.h> //also called cstring
#include "object.h"

// String class
class String : public Object {
    public:
        char *str_;
        size_t size_;

        String() : Object() {
            str_ = new char[1];
            str_[0] = '\0';
            size_ = 1;
        }

        String(const char* str) : Object() {
            size_ = strlen(str);
            str_ = new char[size_ + 1];

            strcpy(str_, str);
        }

        // returns the length of the string
        size_t length() {
            return size_;
        }

        // hashes the string
        size_t hash() {
            size_t res = 0;
            for (int i = 0; i < size_; i++) {
                res += str_[i];
            }
            return res;
        }

        // returns a new string combining this string with s
        String* concat(String* s) {
            char* str = new char[size_ + s->size_ - 1];
            strcpy(str, str_);
            strcat(str, s->str_);
            return new String(str);
        }

        // returns positive number if the ascii values > ascii values of s
        int compare(String* s) {
            for (size_t x = 0; x < size_; x++) {
                if (str_[x] != s->str_[x]) {
                    return str_[x] - s->str_[x];
                }
            }
            return str_[size_] - s->str_[size_];
        }

        // returns true if other is a string * and the characters in str_ are the 
        // same as the characters in other->str_
        bool equals(Object *other){
            String* t = dynamic_cast<String*>(other);
            if (size_ == t->size_) {
                for (int x = 0; x < size_; x++) {
                    if (str_[x] != t->str_[x]) {
                        return false;
                    }
                }
            }
            else {
                return false;
            }
            return true;
        }

        virtual ~String() {
            delete str_;
        }
};

class StringCount: public String{
    public:
        size_t count_;

        StringCount(const char* str, size_t count) : String(str) {
            count_ = count;
        }

        void incriment() {
            count_ += 1;
        }

        size_t count() {
            return count_;
        }

        int compare(StringCount* s) {
            if (this->count() == s->count()) {
                return 0;
            }
            else {
                return s->count() - this->count();
            }
        }
};
