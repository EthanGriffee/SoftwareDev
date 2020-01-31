Queue : https://github.com/Buntry/swdev20_a1p2

Implementation :
    A class Node was created which consisted of two fields: Node* next and Object* obj. To create a
    Node, an object has to be passed in, and it will be set to obj, while next is set to a
    nullpointer. The class has three methods, getters for obj and next, and a setter for next.

    It was decided that queue would contain two fields: Node* first, and a unsigned long len. Len
    was decided to be an unsigned long as the size() function returned an unsigned long.

    When a queue is created, the first is set to a nullpointer and len is set to 0. When enqueue is
    called len is incrimented by one. If first is a nullpointer a new node will be created with the 
    object passed in. If not, then first is traversed using first->getNext(), until a node is found
    with getNext() equaling a nullpointer. This would be the last Node in the queue. A New node is
    created and the last node's next is set to the created node.

    To delete a queue a private helper function called delete_nodex_ is called. This helper fucntion
    traverses the nodes using getNext(), and deletes every node. This function is used both in 
    ~Queue() and in clear().



Specifications : 
    Very specific specifications.




Array : https://github.com/LalBirali/A1P2

Implementation :

Specifications :


Map : https://github.com/grahamwren/cs4500-assignment_1-part2

Implementation :
    A class Map_Node was created which consisted of two fields: Object* key and Object* value. Map
    node extends object so it can be used in an array. To create a Map_Node a key and a value must
    be passed in. The Map_node's methods include changeValue, two getters for value and node, and
    equals. Equals returns true if the the other object is equal to mapnode's key. There is also a
    setter to change the value of value.

    The map object contains three fields: An Array** called hashmap, using the implementation of
    array described above, a size_t num_elements, representing the number of elements in the map,
    and a const size_t MAX_HASH_LENGTH, which is the amount of Arrays in the hashmap, set to 100.

    Creating a map object creates all the arrays in the hashmap, and sets the size to 0. Freeing a
    map object deletes all the arrays in the hashmap, and deletes the hasmap.

    To determine what array a key would be in, a private function findArray_ method was created,
    which hashes the object, and takes the modulus of that and the MAX_HASH_LENGTH. It then returns
    the array at that position in hashmap.

    The set method uses findArray_ on the key. It then searches the returned array for the key using 
    indexOf(). If indexOf returns -1, a new Map_node is created with the input key and value.
    Num_elements is also incrimented by one. If it does not return -1, the setValue method is used
    on the Map_Node at the position returned by indexOf.

    Get uses findArray_ on the key, and searches the array returned using indexOf for the key. If
    indexOf returns -1, a nullpointer is returned, else, the Map_Node at the position's value is 
    returned.

    The remove method uses findArray_ on the key. It then searches the returned array for the key
    using indexOf(). If indexOf returns -1, then nothing happens. 
    

Specifications :