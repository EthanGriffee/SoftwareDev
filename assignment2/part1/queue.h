#pragma once
#include "object.h"
#include "string.h"

class Node {
    public:
      Node* next;
      Object* obj;

      Node(Object* obj) {
        this->obj = obj;
        this->next = nullptr;
      }

      ~Node() {

      }

      Object* getObj() {
        return obj;
      }

      Node* getNext() {
        return next;
      }

      void setNext(Node* next) {
        this->next = next;
      }
};

/**
 * @brief Represents a FIFO queue for containing objects.
 * 
 */
class Queue : public Object {
  public:
    Node* first;
    unsigned long len;

    /**
     * @brief Constructs a new empty Queue object.
     * 
     */
    Queue() {
      first = nullptr;
      len = 0;
    }

    /**
     * @brief Destroys the Queue object.
     * This will delete all objects currently in the queue.
     */
    ~Queue() {
      _delete_nodes();
      delete len;
    }
    
    /**
     * @brief private helper function called by deleter and clear to 
     * delete all objects
     */
    void _delete_nodes() {
      Node* deleting = first;
      while (deleting) {
        Node* old = deleting;
        deleting = deleting->getNext();
        delete old;
      }
    }

    /**
     * @brief Adds the given object to the queue.
     * 
     * @param other 
     */
    void enqueue(Object *other) {
      len += 1;
      if(first) {
        Node* node = first;
        while (node->getNext()) {
          node = node->getNext();
        }
        Node* new_node = new Node(other);
        node->setNext(new_node);
      }
      else {
        first = new Node(other);
      }

    }

    /**
     * @brief Removes an object from the queue, returning
     * nullptr if the queue is empty.
     * 
     * @return Object* 
     */
    Object* dequeue() {
      if(first) {
        Object* returning = first->getObj();
        len -= 1;
        Node* old_node = first;
        first = first->getNext();
        delete old_node;
        return returning;
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
      if (first) {
        return first->getObj();
      }
      else {
        return nullptr;
      }
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
      _delete_nodes();
      len = 0;
      first = nullptr;
    }

    /**
     * @brief Returns the hashcode of this Queue.
     * 
     * @return unsigned long 
     */
    virtual unsigned long hash() {
      unsigned long counter = 0;
      Node* n = first;
      while (n) {
        counter += n->getObj()->hash();
        n = n->next;
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
      if (!queue || queue->size() != this->len) {
          return false;
      }
      Node* n = first;
      Node* n2 = queue->first;
      while (n) {
        if (!n->getObj()->equals(n2->getObj())) {
          return false;
        }
        n = n->getNext();
        n2 = n2->getNext();
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
    Queue* queue;
    /**
     * @brief Constructs a new empty StrQueue object.
     * 
     */
    StrQueue() {
      queue = new Queue();
    }

    /**
     * @brief Destroys the StrQueue object.
     * This will delete all strings currently in the queue.
     */
    ~StrQueue() {
      delete queue;
    }

    /**
     * @brief Adds the given string to the queue.
     * 
     * @param other 
     */
    void enqueue(String *other) {
      queue->enqueue(other);
    }

    /**
     * @brief Removes a string from the queue, returning
     * nullptr if the queue is empty.
     * 
     * @return String* 
     */
    String* dequeue() {
      return static_cast <String*> (queue->dequeue());

    }

    /**
     * @brief Returns, but doesn't remove, the head of the queue.
     * Returns nullptr if the queue is empty.
     * 
     * @return String* 
     */
    String* peek() {
      return static_cast <String*> (queue->peek());
    }

    /**
     * @brief Returns the number of elements in the queue.
     * 
     * @return unsigned long 
     */
    unsigned long size() {
      return queue->size();
    }

    /**
     * @brief Returns whether the queue contains any elements.
     * 
     * @return bool 
     */
    bool is_empty() {
      return queue->is_empty();
    }

    /**
     * @brief Removes all elements from the queue, deleting them.
     */
    void clear() {
      queue->clear();
    }

    /**
     * @brief Returns the hashcode of this Queue.
     * 
     * @return unsigned long 
     */
    virtual unsigned long hash() {
      return queue->hash();
    }

    /**
     * @brief Determines whether this queue is equal to the
     * given object.
     * 
     * @param o 
     * @return bool
     */
    virtual bool equals(Object* o) {
      StrQueue * input = dynamic_cast<StrQueue*>(o);
      if (!input) {
          return false;
      }
      else {
        return queue->equals(input->queue);
      }
    }
};