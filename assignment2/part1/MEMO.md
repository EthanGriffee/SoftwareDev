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

    Different methods traverse the Nodes using the get function to look at all items in the queue.

    String queue was decided to be an Object, and contain a queue, so return functions can be String
    instead of Object*, and to better enforce adding to a queue.





Specifications : 

    Documentation quality: The specification for queue by our Spec pair was well written. It was
    easy to follow along their interface and the comments were helpful in figuring out the code. 

    Responsiveness: The Spec pair for Queue were easy to work with. They were quick to respond when
    we reported small issues which was helpful and time saving!

    Test Quality: The test file provided by our Spec pair contained a small amount issues that were
    causing memory leaks. However, once we bought this to their attention, they quickly resolved the
    issue!




Array : https://github.com/LalBirali/A1P2

Implementation :
    We used a Object** to represesnt the contents of an array, and a size_t to keep track fo the
    length. We also had a second size_t called max_length to keep track of the maximum length
    allocated for Object**. When the size of the array approched the max_length Object**'s contents
    were coppied into a new Array with a larger maximum length.





Specifications:
    Documentation quality: The specification for array by our Spec pair was fine for most of the
    part, however, their implementation of IntArray, FloatArray and BolArray classes seem wrong as
    we cannot write a get function that returns int, float or Boolean because the Array's get
    returns an object and IntArray, FloatArray and BolArray are subclasses of Array.

    Responsiveness: The Spec pair for Array’s were easy to work with. They were quick to reply when
    we reported an issue. However, they didn’t solve the we pertained with the get function in the
    IntArray, FloatArray and BolArray classes having the wrong return type.

    Test Quality: The test file provided by our Spec pair didn’t include test for the different
    types of datatypes such as int, float or Boolean. They added it as per our request. 


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
    using indexOf(). If indexOf returns -1, then nothing happens. Else, it calls the remove() method
    on the array, and decreases num_elements by one. 

    The has method uses findArray_ on the key. It returns whether the indexOf(key) is equal to -1.

    The clear method calls the Array's clear function for every array in hashmap, and sets 
    num_elements to 0.

    The size method returns num_elements. 

    The keys method goes through every array in hashmap, and adds every Map_Node's key found in each
    array to Object** dest.

    The equals method calls other's equals on this when Object is entered. When a Map is entered the
    equals method makes sure this map, and the other maps have the same size. Then it uses the keys()
    function on other to iterate through every key pair in this and other. It calls if this map's
    get of the key equals the other map's get of the key. If all keys have the same value pair it 
    returns true. 

    Hash iterates through the arrays in hashmap, and adds their hashes together.

Specifications :

    The documentation quality was very good. They provided all the information needed to implement
    their specification without any clarification. We did not have to communicate with this team
    much, because other teams had ironed out all the problems. They test quality was pretty good, 
    they tested all methods thoroughly. However, they did not add deletes to the objects they
    created, making it hard to know if our implementation was leaking memory.


    Documentation quality: The specification for map by our Spec pair was well written. It was easy
    to follow along their interface and the comments were helpful in figuring out the code. 

    Responsiveness: We did not have any issues with their code; hence, we cannot comment on this
    topic.

    Test Quality: The test file provided by our Spec pair were good, however, they did not add
    deletes to the objects they created, making it hard to know if our implementation was leaking
    memory.