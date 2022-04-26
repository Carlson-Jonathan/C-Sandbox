#include <iostream> 
using namespace std;
#include "linkedList.h"

int main() {

    LinkedList<Node> myList;
    
    myList.printList();
    cout << "Size: " << myList.size() << endl;
    cout << "---------------------" << endl;

    Node* newNode = new Node;
    newNode->value = "New Node";
    
    myList.insert(newNode, myList.size());
    myList.printList();
    cout << "Size: " << myList.size() << endl;
    cout << "---------------------" << endl;

    myList.erase(0);
    myList.printList();    
    cout << "Size: " << myList.size() << endl;
    cout << "---------------------" << endl;

    myList.erase(0);
    // myList.printList();    
    cout << "Size: " << myList.size() << endl;
    cout << "---------------------" << endl;

    
    return 0;
}