#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;
    
// This is a generic datatype example I created for working with my linked list.
struct Node {
    string value = "Head";
    Node* before = NULL;
    Node* after = NULL;
};

#endif // NODE_H
