#pragma once
#include <stdlib.h>
#include "Object.h"


/**
 * This class represents an Array, more akin to a dynamic ArrayList type
 * versus a fixed-sized array, which may already be represented or built-in in CwC.
 * This interface offers the overall main functionalities:
 *      Addition of elements
 *      Addition of Arrays
 *      Removal of elements
 *      Indexing by Element
 *      Get Element by Index
 *      Equality
 *      Replacing elements at an Index
 * This class CAN be implemented using an underlying array structure that is dynamically resized. 
 * Note that the inital memory outlay is an array of pointers of size 10. We wish to reduce
 * the amount of resizing of the array, which would make several operations have O(n) time instead
 * of O(1) time. The below fields exist to serve as an example of how to implement. 
 * There are several STUB implementations in this API: In order to write a StringArray
 * you will need to extend Array and correctly override the virtual functions. 
 **/
class Array : public Object {
public:
    Object** array;
    size_t size;
    size_t max_capacity;

    /**
     * Default constructor which will set the initial max-capacity to the array to 10. 
     **/
    Array() {
        max_capacity = 10;
        size = 0;
        array = new Object*[max_capacity];
    }

    /**
     * Initalized this array with the characteristics of the passed in array.
     * @arg arr Array containing values to be used in initialization. 
     **/
    Array(Array* arr) {
        this->array = arr->array;
        this->size = arr->size;
        this->max_capacity = arr->max_capacity;
    }

    /**
     * Destructor which will free the memory of the underlying array as well. 
     **/
    ~Array() {
        delete[] array;
    }

    /**
     * Will return the Object pointer at the provided index. if the index is invalid, 
     * then the method will return NULL.
     * @arg index Location to get the value in the array at. 
     **/
    virtual Object* get(size_t index) {
        if (index > size) {
            return NULL;
        }
        return array[index];
    }


    /**
     * Clears the array and reinitializes the underlying array to 10 spots with no elements. 
     * Reinitializes the size to 0. 
     **/
    virtual void clear() {
        delete[] array;
        max_capacity = 10;
        size = 0;
        array = new Object*[max_capacity];
    }

    /**
     * Resizing the underlying array. And then copying over the elements to a new array with
     * the updated size. 
     * Default is doubling the array size when the max capacity of the 
     * underlying array less the number of elements is 2. 
     **/
    virtual void resize() {
        max_capacity = max_capacity * 2;
        Object** new_array = new Object*[max_capacity];
        for (int x = 0; x < size; x++) {
            new_array[x] = array[x];
        }
        delete[] array;
        array = new_array;
        
    }

    /**
     * Returns the first index of the of given Object pointer. 
     * If the object pointer is not found then -1 is returned.
     * @arg to_find Object to find the index of. 
     **/
    virtual int indexOf(Object* to_find) {
        for (int x = 0; x < size; x++) {
            if(array[x]->equals(to_find)) {
                return x;
            }
        }
        return -1;
    }

    /**
     * Adds the element provided to the end of the list, unless the given element is NULL, 
     * then it will not be added. The size is incremented by 1. If resizing the array is necessary, 
     * then that should be done.
     * @arg to_add Object to be added to the array. 
     **/
    virtual void add(Object* to_add) {
        if (!to_add) {
            return;
        }
        if (size + 2 >= max_capacity) {
            resize();
        }
        array[size] = to_add;
        size += 1;
    }

    /**
     * Adds the provided array to the end of the list, unless the given array is NULL, 
     * then it will not be added. 
     * Assuming a valid move, the size of this array is incremented by the size of the 
     * added array. If resizing the array is necessary, then that should be done.
     * @arg to_add Array of Objects that all need to be added to this array. 
     **/
    virtual void addAll(Array* to_add) {
        size_t add_length = to_add->getSize();
        while (size + add_length + 2 >= max_capacity) {
            resize();
        }
        for (size_t i = 0; i < add_length; i++) {
            add(to_add->get(i));
        }
    }

    /**
     * Adds the provided object at the given index, unless the given object is NULL, 
     * then it will not be added. Otherwise, all elements previously at the index and
     * to the right will be shifted accordingly. 
     * If the index is invalid, then nothing will be added/shifted. 
     * The size of this array is incremented by 1. 
     * If resizing the array is necessary, then that should be done. 
     * @arg to_add Object to be added to the array
     * @arg index Location to add the Object at
     **/
    virtual void add(Object* to_add, size_t index) {
        if (index > size) {
            return;
        }
        if (size + 2 >= max_capacity) {
            resize();
        }
        size += 1;
        for (int x = size; x > index; x--){
            array[x] = array[x - 1];
        }
        array[index] = to_add;
    }

    /**
     * Adds all the elements of the provided array at the given index, 
     * unless the given array is NULL, then it will not be added. Otherwise, 
     * all elements previously at the index and
     * to the right will be shifted accordingly by the size of the procided array, 
     * If the index is invalid, then nothing will be added/shifted.
     * Assuming a valid move, the size of this array is incremented by the size of the 
     * added array.  If resizing the array is necessary, then that should be done.
     * @arg to_add Array of Objects to be added to the array
     * @arg index Location to add the objects to the array at
     **/
    virtual void addAll(Array* to_add, size_t index) {
        if (index > size) {
            return;
        }
        size_t add_length = to_add->getSize();
        while (size + add_length + 2 >= max_capacity) {
            resize();
        }
        size += add_length;
        for (int x = size - 1; x >= index + add_length; x--){
            array[x] = array[x - add_length];
        }
        for (int x = 0; x < add_length; x++){
            array[index + x] = to_add->get(x);
        }
    }

    /**
     * Returns the subarray starting from the provided index to the end of the array. 
     * If the index is invalid, then the method returns NULL
     * @arg index Starting place for the subarray
     **/
    virtual Array* subArray(size_t index) {
        return subArray(index, size);
    }

    /**
     * Returns the subarray starting from the provided index to the ending index
     * The starting index must always be greater than the ending index. If either index is invalid, 
     * then NULL is returned. The set is [start, end)
     * @arg startIndex starting place for the subarray
     * @arg endIndex location of the last object to be put in the subarray
     **/
    virtual Array* subArray(size_t startIndex, size_t endIndex) {
        if (startIndex > endIndex || endIndex > size) {
            return NULL;
        }
        Array* arr = new Array();
        while (startIndex < endIndex) {
            arr->add(this->get(startIndex));
            startIndex += 1;
        }
        return arr;
    }

    /**
     * Removes the first instance of the given Object in this array. If nothing 
     * is found, then no action will occur. The size reduces by 1 if the 
     * element is found.
     * @arg to_remove Object to be removed from the array
     **/
    virtual void remove(Object* to_remove) {
        for (size_t i = 0; i < size; i ++) {
            if (this->get(i)->equals(to_remove)) {
                size -= 1;
                for (int x = i; x < size; x++) {
                    array[x] = array[x + 1];
                }
                return;
            }
        }
    }

    /**
     * Removes all instances of the given Object in this array. If nothing 
     * is found, then no action will occur. The size reduces the number of found
     * elements there are.
     * @arg to_remove Object that all instances in the array will be removed of
     **/
    virtual void removeAll(Object* to_remove) {
        for (size_t i = 0; i < size; i ++) {
            if (this->get(i)->equals(to_remove)) {
                size -= 1;
                for (int x = i; x < size; x++) {
                    array[x] = array[x + 1];
                }
                i-=1;
            }
        }
    }

    /**
     * Returns number of elements in the array. 
     **/
    virtual size_t getSize() {
        return size;
    }

    /**
     * Overriding the Object equals method. 
     * Returns if all the elements in this array and the given object are equal and 
     * in the same other. 
     * If the given object is NULL or not an array, then false will be returned.
     * @arg other Object to check if this array is equal to
     **/
    bool equals(Object* other) {
        Array * arr = dynamic_cast<Array*>(other);
        if (arr == nullptr || arr->getSize() != size) {
            return false;
        }
        for (size_t x = 0; x < size; x++) {
            if (!array[x]->equals(arr->get(x))) {
                return false;
            }
        }
        return true;
    }

    /**
     * Overriding the Object hash_me() method. 
     * Hashes the array based on user specifications. Default implementation is
     * to hash all internal elements and sum them up. 
     **/
    size_t hash_me_() {
        size_t n = 0;
        for(int x = 0; x < size; x++) {
            n += array[x]->hash();
        }
        return n;
    }
};

/**
 * Incomplete implementation of String Array. No methods overriden from
 * Array. Created for testing purposes, so we can design tests. 
 **/
class StringArray : public Array {

    public: StringArray() : Array() {

    }

};