#pragma once

// lang::CwC

#include "object.h"
#include "string.h"
#include "Array.h"


class Map_Node : public Object {
    public:
        Object* key;
        Object* value;

        Map_Node(Object* key, Object* value) {
            this->key = key;
            this->value = value;
        }

        void changeValue(Object* new_val) {
            this->value = new_val;
        }

        Object* getKey() {
            return key;
        }

        Object* getValue() {
            return value;
        }

        bool equals(Object* other) {
            return other->equals(key);
        }
};

/**
 * A dictionary of string keys and object values.  All keys and values are owned
 * by the caller, and none of the map's methods will modify them.  Keys which
 * are .equals are equal, i.e. the map will never contain two keys which are
 * extensionally equivalent at the same time.
 */

class Map : public Object
{
    public:
        Array** hashmap;
        size_t num_elements;
        const size_t MAX_HASH_LENGTH = 100;

        Map() {
            hashmap = new  Array*[MAX_HASH_LENGTH];
            for (size_t x = 0; x < MAX_HASH_LENGTH; x++) {
                hashmap[x] = new Array();
            }
            num_elements = 0;
        }

        virtual ~Map(){
            for (size_t x = 0; x < MAX_HASH_LENGTH; x++) {
                delete hashmap[x];
            }
            delete hashmap;
        };

        /**
         * Returns the value which was set for this key.
         * Returns nullptr if not in map.
         */
        virtual Object *get(Object *key) {
            Array* arr = hashmap[key->hash() % MAX_HASH_LENGTH];
            int x = arr->indexOf(key);
            if (x == -1) {
                return nullptr;
            }
            else {
                return static_cast<Map_Node*> (arr->get(x))->getValue(); 
            }
        }

        /**
         * Set the value at the given key in this map.
         */
        virtual void set(Object *key, Object *value) {
            Array* arr = hashmap[key->hash() % MAX_HASH_LENGTH];
            int x = arr->indexOf(key);
            if (x == -1) { 
                num_elements += 1;
                return arr->add(new Map_Node(key, value));
            }
            else {
                Map_Node* m = static_cast<Map_Node*> (arr->get(x));
                m->changeValue(value);
            }

        }

        /**
         * Remove the value at the given key in this map. No-op if value not in map.
         */
        virtual void remove(Object *key) {
            Array* arr = hashmap[key->hash() % MAX_HASH_LENGTH];
            if (arr->indexOf(key) != -1) {
                arr->remove(key);
                num_elements -= 1;
            }
        }

        /**
         * Determine if the given key is in this map.
         */
        virtual bool has(Object *key) {
            Array* arr = hashmap[key->hash() % MAX_HASH_LENGTH];
            return arr->indexOf(key) != -1;
        }

        /**
         * Remove all keys from this map.
         */
        virtual void clear() {
            for (int i = 0; i < MAX_HASH_LENGTH ; i++) {
                hashmap[i]->clear();
            }
            num_elements = 0;
        }

        /**
         * Return the number of entries in this map.
         */
        virtual size_t size() {
            return num_elements;
        }

        /**
         * Store keys in the given array. Caller responsible for allocating at least
         * Map::size() elements.
         */
        virtual void keys(Object **dest) {
            size_t count = 0;
            for (int i = 0; i < MAX_HASH_LENGTH; i++) {
                Array* arr = hashmap[i];
                for (int x = 0; x < arr->getSize(); x++) {
                    dest[count] = static_cast<Map_Node*> (arr->array[x])->getKey();
                    count += 1;
                }
            }
        }

        virtual bool equals(Object* other) {
            return other->equals(this);
        }

        virtual bool equals(Map* other) {
            if (other->size() != num_elements) {
                return false;
            }
            Object** other_keys = new Object*[other->size()];
            other->keys(other_keys);
            for (int i = 0; i < other->size(); i++) {
                if (!other->get(other_keys[i])->equals(this->get(other_keys[i]))) {
                    delete[] other_keys;
                    return false;
                }
            }
            delete[] other_keys;
            return true;
        }

        size_t hash() {
            size_t count = 0;
            for (int i = 0; i < MAX_HASH_LENGTH; i++) {
                count += hashmap[i]->hash();
            }
        }

    
};