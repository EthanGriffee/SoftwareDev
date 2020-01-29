#pragma once
#include "object.h"

/**
 * @brief Represents a FIFO queue for containing objects.
 * 
 */
class Queue : public Object {
  public:
    /**
     * @brief Constructs a new empty Queue object.
     * 
     */
    Queue();
    
    /**
     * @brief Constructs a new Queue object as a copy of the given queue.
     * 
     * @param q 
     */
    Queue(Queue& q);

    /**
     * @brief Destroys the Queue object.
     * This will delete all objects currently in the queue.
     */
    ~Queue();

    /**
     * @brief Adds the given object to the queue.
     * 
     * @param other 
     */
    void enqueue(Object *other);

    /**
     * @brief Removes an object from the queue, returning
     * nullptr if the queue is empty.
     * 
     * @return Object* 
     */
    Object* dequeue();

    /**
     * @brief Returns, but doesn't remove, the head of the queue.
     * Returns nullptr if the queue is empty.
     * 
     * @return Object* 
     */
    Object* peek();

    /**
     * @brief Returns the number of elements in the queue.
     * 
     * @return unsigned long 
     */
    unsigned long size();

    /**
     * @brief Returns whether the queue contains any elements.
     * 
     * @return bool 
     */
    bool is_empty();

    /**
     * @brief Removes all elements from the queue, deleting them.
     */
    void clear();
};
