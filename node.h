#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;
    
struct Node {
    string value = "Head";
    Node* before = NULL;
    Node* after = NULL;
};

#endif // NODE_H