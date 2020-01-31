#pragma once
#include "object.h"
#include "string.h"

/**
 * @brief Represents a FIFO queue for containing objects.
 * 
 */
struct Node {
  Node* next;
  Object* obj;
};

class Queue : public Object {
  public:
    Node* first;
    unsigned long len;

    /**
     * @brief Constructs a new empty Queue object.
     * 
     */
    Queue() {
      first = new Node;
      first->next = nullptr;
      first->obj = nullptr;
      len = 0;
    }

    /**
     * @brief Destroys the Queue object.
     * This will delete all objects currently in the queue.
     */
    ~Queue() {
      _delete_objects();
      delete first;
    }
    
    /**
     * @brief private helper function called by deleter and clear to 
     * delete all objects
     */
    void _delete_objects() {
      while (first->next) {
        Node* old = first;
        first = first->next;
        delete old;
      }
      if (first->obj) {
        delete first->obj;
      }
    }

    /**
     * @brief Adds the given object to the queue.
     * 
     * @param other 
     */
    void enqueue(Object *other) {
      len += 1;
      Node* node = first;
      if(first->obj) {
        while (node->next) {
          node = node->next;
        }
        Node* new_node = new Node;
        new_node->next = nullptr;
        new_node->obj = other;
        node->next = new_node;
      }
      else {
        first->obj = other;
      }

    }

    /**
     * @brief Removes an object from the queue, returning
     * nullptr if the queue is empty.
     * 
     * @return Object* 
     */
    Object* dequeue() {
      if(first->obj) {
        Object* returning = first->obj;
        len -= 1;
        if(first->next) {
          first = first->next;
          return returning;
        }
        else {
          first->obj = nullptr;
          return returning;
        }
      }
      else {
        return nullptr;
      }

    }

    /**
     * @brief Returns, but doesn't remove, the head of the queue.
     * Returns nullptr if the queue is empty.
     * 
     * @return Object* 
     */
    Object* peek() {
      return first->obj;
    }

    /**
     * @brief Returns the number of elements in the queue.
     * 
     * @return unsigned long 
     */
    unsigned long size() {
      return len;
    }

    /**
     * @brief Returns whether the queue contains any elements.
     * 
     * @return bool 
     */
    bool is_empty() {
      return len == 0;
    }

    /**
     * @brief Removes all elements from the queue, deleting them.
     */
    void clear() {
      _delete_objects();
      len = 0;
      first->next = nullptr;
      first->obj = nullptr;
    }

    /**
     * @brief Returns the hashcode of this Queue.
     * 
     * @return unsigned long 
     */
    virtual unsigned long hash() {
      unsigned long counter = 0;
      Node* n = first;
      while (n->next) {
        counter += n->obj->hash();
        n = n->next;
      }
      if (n->obj) {
        counter += n->obj->hash();
      }
      return counter;
    }

    /**
     * @brief Determines whether this queue is equal to the
     * given object.
     * 
     * @param o 
     * @return bool
     */
    virtual bool equals(Object* o) {
      Queue * queue = dynamic_cast<Queue*>(o);
      if (queue == nullptr || queue->size() != queue->len) {
          return false;
      }
      Node* n = first;
      Node* n2 = queue->first;
      while (n->next) {
        if (!n->obj->equals(n2->obj)) {
          return false;
        }
        n = n->next;
        n2 = n2->next;
      }
      if (n->obj) {
         return n->obj->equals(n2->obj);
      }
      return true;
    }
};

/**
 * @brief Represents a FIFO queue for containing strings.
 * 
 */
class StrQueue : public Object {
  public:
    /**
     * @brief Constructs a new empty StrQueue object.
     * 
     */
    StrQueue() {

    }

    /**
     * @brief Destroys the StrQueue object.
     * This will delete all strings currently in the queue.
     */
    ~StrQueue() {

    }

    /**
     * @brief Adds the given string to the queue.
     * 
     * @param other 
     */
    void enqueue(String *other) {

    }

    /**
     * @brief Removes a string from the queue, returning
     * nullptr if the queue is empty.
     * 
     * @return String* 
     */
    String* dequeue() {

    }

    /**
     * @brief Returns, but doesn't remove, the head of the queue.
     * Returns nullptr if the queue is empty.
     * 
     * @return String* 
     */
    String* peek() {

    }

    /**
     * @brief Returns the number of elements in the queue.
     * 
     * @return unsigned long 
     */
    unsigned long size() {

    }

    /**
     * @brief Returns whether the queue contains any elements.
     * 
     * @return bool 
     */
    bool is_empty() {

    }

    /**
     * @brief Removes all elements from the queue, deleting them.
     */
    void clear() {

    }

    /**
     * @brief Returns the hashcode of this Queue.
     * 
     * @return unsigned long 
     */
    virtual unsigned long hash() {

    }

    /**
     * @brief Determines whether this queue is equal to the
     * given object.
     * 
     * @param o 
     * @return bool
     */
    virtual bool equals(Object* o) {
      
    }
};