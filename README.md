# Linked-List
<h3>Description</h3>
<p>This is a 'Linked List' datatype class for C++. Linked lists are not part 
  of the C++ standard library, and I occasionally need them, so made one. 
  Any class, struct or primitive datatype can be used.</p>
<h3>Features</h3>
<ul><li>size() : Integer<p>Returns the size of the linked list.</p></li>
    
    int sizeOfList = linkedList.size();

<li>getElement(int) : Node*<p>Gets an element node at the index parameter.</p></li>

    Node* node = linkedList.getElement(4);

<li>insert(Node*, int) : void<p>Inserts a node into a linked list at the index parameter.</p></li>

    Node* nodeToInsert = new Node;
    linkedList.insert(nodeToInsert, 7);
    
<li>erase(int) : void<p>Removes the node at the index parameter.</p></li>

    linkedList.erase(9);

<li>makeListCircular() : void<p>Connects the linked list's head and tail (first and last) elements.</p></li>

    linkedList.makeListCircular();    
    
<li>printList() : void<p>Displays information about the linked list in the console. Because the 
    datatypes used can vary, this function needs to be configured to work with your datatype.
</p></li>

    linkedList.printList();    
</ul>

<h3>Setup and Instructions For Use</h3>

1. ) `#include` your datatype (class/struct) in the `linkedList.h` file.</li>
2. ) In your class/struct file, set pointers of your object and name them `before` and `after`.
     Be sure to initialize these pointers with `NULL`.
3. ) To use the `LinkedList::printList()` function, edit the `cout` line in `linkedList.h` to
     show the information you want to see about your class or struct.
  
