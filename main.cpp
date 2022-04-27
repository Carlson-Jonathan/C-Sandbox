#include <iostream>
#include <vector>
using namespace std;

#include "linkedList.h"
#include "node.h"

// -------------------------------------------------------------------------------------------------

bool size_test(string & error) {
    
    LinkedList<Node> newList; 
    if(newList.size()) {
        error = "Size of empty list is not 0: (size = " + to_string(newList.size()) + ")";
        return false;
    } 

    newList.head = new Node; 
    if(newList.size() != 1) {
        error = "Size of single item list is not 1: (size = " + to_string(newList.size()) + ")";
        return false;
    }    

    newList.head->after = new Node;
    newList.head->after->after = new Node;
    newList.head->after->after->after = new Node;
    newList.head->after->after->after->after = new Node;
    
    if(newList.size() != 5) {
        error = "Size of five item list is not 5: (size = " + to_string(newList.size()) + ")";
        return false;
    } 
    
    return true;
}

// -------------------------------------------------------------------------------------------------

bool getElement_test(string & error) {

    LinkedList<Node> newList;

    newList.head = new Node;
    newList.head->after = new Node;
    newList.head->after->value = "Second Element";
    newList.head->after->after = new Node;
    newList.head->after->after->value = "Third Element";    
    newList.head->after->after->after = new Node;
    newList.head->after->after->after->value = "Fourth Element";    
    newList.head->after->after->after->after = new Node;
    newList.head->after->after->after->after->value = "Fifth Element";

    vector<string> expectedResults = 
        {"Head", "Second Element", "Third Element", "Fourth Element", "Fifth Element"};
    
    for(int i = 0; i < 5; i++) {
        string output = newList.getElement(i)->value;
        if(output != expectedResults[i]) {
            error = "Incorrect element retrieved: \n\tExpected: '" + expectedResults[i] +
                    "'\n\tReceived: '" + output + "'";
            return false;
        }
    }
    
    return true;
}

// -------------------------------------------------------------------------------------------------
// This test depends on prior tests working.
bool insert_test(string & error) {
    LinkedList<Node> newList;

    newList.insert(new Node, 0);
    if(newList.size() != 1) {
        error = "Failed to insert first item into empty list.";
        return false;
    }

    // Populate a linked list of 10 elements and set their values.
    for(int i = 1; i < 10; i++) {
        newList.insert(new Node, i);
        newList.getElement(i)->value = to_string(i);
    }

    // Replace the head element with a new insert.
    Node* newNode = new Node;
    newNode->value = "New Insertion";
    newList.insert(newNode, 0);
    if(newList.head->value != "New Insertion") {
        error = "Failed to replace head (index 0) with new insert.";
        return false;
    }
    
    // Random insertions.
    for(int i = 0; i < newList.size(); i += 3) {
        Node* newNode = new Node;
        newNode->value = "Insert " + to_string(i);
        newList.insert(newNode, i);
    }  

    vector<string> expectedResults = 
        {"Insert 0", "Insert 3", "Insert 6", "Insert 9", "Insert 12", "Insert 15"};
    
    for(int i = 0, j = 0; i < newList.size(); i += 3, j++) {
        if(newList.getElement(i)->value != expectedResults[j]) {
            error = "Failed to insert element " + to_string(i) + 
                    " to the correct index:\n\tExpected: '" + expectedResults[j] + 
                    "'\n\tReceived: '" + newList.getElement(i)->value + "'";
            return false;
        }
    }

    Node* pushBack = new Node;
    pushBack->value = "Push Back";
    newList.push_back(pushBack);
    if(newList.getElement(newList.size() - 1)->value != "Push Back") {
        error = "push_back() is not inserting elements at the end of the list.";
        return false;
    }

    return true;
}

// -------------------------------------------------------------------------------------------------
// This test depends on prior tests working.
bool erase_test(string & error) {

    LinkedList<Node> newList;
    
    for(int i = 0; i < 10; i++) {
        newList.insert(new Node, i);
        if(i) newList.getElement(i)->value = to_string(i);
    }
    
    newList.makeListCircular();
    newList.printList();

    // Single erase.
    newList.erase(7);
    for(int i = 0; i < newList.size(); i++) {
        string currentValue = newList.getElement(i)->value;
        if(currentValue == "7") {
            error = "Indicated element is not being erased properly.";
            return false;
        }
    }

    newList.printList();
    
    // Erase and replace head.
    newList.getElement(0)->value = "Head";
    newList.erase(0);
    if(newList.head->value != "1") {
        error = "Head is not being erased/replaced correctly.";
        return false;
    }

    newList.printList();
    
    // Erase last element.
    newList.erase(newList.size() - 1);
    for(int i = 0; i < newList.size(); i++) {
        string currentValue = newList.getElement(i)->value;
        if(currentValue == "9") {
            error = "Last element is not being erased properly.";
            return false;
        }
    }

    newList.printList();
    
    // Erase entire list.
    int size = newList.size();
    for(int i = 0; i < size; i++) {
        cout << "======== Erase entire list ========" << endl;
        newList.erase(0);
        newList.printList();
    }

    
    if(newList.head) {
        error = "Unable to erase entire list:\n\tList size = " + to_string(newList.size()) +
                "\n\tHead pointer is NULL = " + to_string(newList.head == NULL);
        return false;
    }

    newList.printList();
    
    return true;
}

// -------------------------------------------------------------------------------------------------

bool makeListCircular_test(string & error) {

    LinkedList<Node> newList;
    
    for(int i = 0; i < 10; i++) {
        newList.insert(new Node, i);
        newList.getElement(i)->value = to_string(i);
    }

    newList.makeListCircular();

    if(newList.size() != 10) {
        error = "size() is incompatible with a circular list.";
        return false;            
    }
    
    for(int i = 0; i < newList.size(); i++) {
        if(newList.getElement(i)->value != to_string(i)) {
            error = "getElement(" + to_string(i) + ") is incompatible with a circular list.";
            return false;
        }
    }

    Node* newNode = new Node;
    newNode->value = "New Insert";
    newList.insert(newNode, 4);
    
    // newList.printList();
    // cout << "List size: " << newList.size() << endl;
    
    return true;
}

// -------------------------------------------------------------------------------------------------

int main() {

    string error    = "";
    bool size       = size_test(error),
         getElement = getElement_test(error),
         insert     = insert_test(error),
         erase      = erase_test(error),
         circular   = makeListCircular_test(error);

    vector<pair<bool, string>> results = {
        {size,       "size_test()"},
        {getElement, "getElement_test()"},
        {insert,     "insert_test()"},
        {erase,      "erase_test()"},
        {circular,   "makeListCircular_test()"}   
    };

    cout << "===================================\n"
         << "Unit test results for LinkedList.h:\n"
         << "===================================" 
         << endl;
    
    for(int i = 0; i < results.size(); i++) {
        if(results[i].first) 
            cout << "PASSED: " << results[i].second << endl;
        else {
            cout << "FAILED: " << results[i].second
                 << "\n\t" << error << endl;
        }
    }

    
    
    return 0;
}