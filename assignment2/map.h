#pragma once

// lang::CwC

#include "object.h"
#include "string.h"

struct Map_Node {
    Object* key;
    Object* value;
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
        Map_Node** m;
        size_t num_elements;
        size_t max_elements;

        Map() {
            m = new  Map_Node*[10];
            num_elements = 0;
            max_elements = 0;
        }

        virtual ~Map(){
            clear();
        };

        /**
         * Returns the value which was set for this key.
         * Returns nullptr if not in map.
         */
        virtual Object *get(Object *key) {
            for (size_t x = 0; x < num_elements; x++) {
                if (m[x]->key->equals(key)) {
                    return m[x]->value;
                }
            }
            return nullptr;
        }

        /**
         * Set the value at the given key in this map.
         */
        virtual void set(Object *key, Object *value) {
            Map_Node* new_mapping = new Map_Node;
            new_mapping->key = key;
            new_mapping->value = value;

            if (! this->has(key)) {
                m[num_elements] = new_mapping;
                num_elements += 1;
                max_elements += 1;
            }

            else {
                for (int i = 0; i < num_elements; i++) {
                    if (m[i]->key->equals(key)) {
                        delete m[i];
                        m[i] = new_mapping;
                    }
                }
            }
        }

        /**
         * Remove the value at the given key in this map. No-op if value not in map.
         */
        virtual void remove(Object *key) {
            size_t index = -1;
            for (int i = 0; i < num_elements; i++) {
                if (m[i]->key->equals(key)) {
                    index = i;
                    break; 
                }
            }
            if (index == -1) {
                return;
            }
            num_elements -= 1;
            delete m[index];
            for (int x = index; x < num_elements; x++) {
                m[x] = m[x + 1];
            }
        }

        /**
         * Determine if the given key is in this map.
         */
        virtual bool has(Object *key) {
            for (size_t x = 0; x < num_elements; x++) {
                if (m[x]->key->equals(key)) {
                    return true;
                }
            }
            return false;
        }

        /**
         * Remove all keys from this map.
         */
        virtual void clear() {
            for (int i = 0; i < num_elements; i++) {
                delete m[i];
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
            for (int i = 0; i < num_elements; i++) {
                dest[i] = m[i]->key;
            }
        }

        virtual bool equals(Object* other) {
            Map * map = dynamic_cast<Map*>(map);
            if (map == nullptr || map->size() != map->num_elements) {
                return false;
            }
        }
};