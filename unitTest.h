#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>
#include <vector>
using namespace std;

#include "linkedList.h"
#include "node.h"

class UnitTest {
private:

    UnitTest() {}

    static bool size_test(string & error, bool testCircularList = false) {
        
        LinkedList<Node> newList; 
        if(newList.size()) {
            error = "Size of empty list is not 0: (size = " + to_string(newList.size()) + ")";
            return false;
        } 
    
        newList.head = new Node; 
        if(testCircularList) newList.makeListCircular();
        
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
    
    static bool getElement_test(string & error, bool testCircular = false) {
    
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
    
        if(testCircular) newList.makeListCircular();
    
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
    // This test depends on prior tests' success.
    static bool insert_test(string & error, bool testCircular = false) {
        LinkedList<Node> newList;
    
        newList.insert(new Node, 0);
        if(newList.size() != 1) {
            error = "Failed to insert first item into empty list.";
            return false;
        }
        
        if(testCircular) newList.makeListCircular();
    
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
        
        // Various body insertions.
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
    
        // Insert as last element (push_back)
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
    // This test depends on prior tests' success.
    static bool erase_test(string & error, bool testCircular = false) {
    
        LinkedList<Node> newList;
        
        for(int i = 0; i < 10; i++) {
            newList.insert(new Node, i);
            if(i) newList.getElement(i)->value = to_string(i);
        }
    
        if(testCircular) newList.makeListCircular();
        
        // Single erase.
        newList.erase(7);
        for(int i = 0; i < newList.size(); i++) {
            string currentValue = newList.getElement(i)->value;
            if(currentValue == "7") {
                error = "Indicated element is not being erased properly.";
                return false;
            }
        }
    
        // Erase and replace head.
        newList.getElement(0)->value = "Head";
        newList.erase(0);
        if(newList.head->value != "1") {
            error = "Head is not being erased/replaced correctly.";
            return false;
        }
        
        // Erase last element.
        newList.erase(newList.size() - 1);
        for(int i = 0; i < newList.size(); i++) {
            string currentValue = newList.getElement(i)->value;
            if(currentValue == "9") {
                error = "Last element is not being erased properly.";
                return false;
            }
        }
    
        // Erase entire list.
        int size = newList.size();
        for(int i = 0; i < size; i++) {
            newList.erase(0);
        }
    
        if(newList.head) {
            error = "Unable to erase entire list:\n\tList size = " + to_string(newList.size()) +
                    "\n\tHead pointer is NULL = " + to_string(newList.head == NULL);
            return false;
        }
    
        return true;
    }
    
    // -------------------------------------------------------------------------------------------------
    
    static bool makeListCircular_test(string & error) {
    
        LinkedList<Node> newList;
        
        for(int i = 0; i < 10; i++) {
            newList.insert(new Node, i);
            newList.getElement(i)->value = to_string(i);
        }
    
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
        
        return true;
    }
    
    static void runTests(vector<pair<bool, string>> results, string error) {
        for(int i = 0; i < results.size(); i++) {
            if(results[i].first) 
                cout << "PASSED: " << results[i].second << endl;
            else {
                cout << "FAILED: " << results[i].second
                     << "\n\t" << error << endl;
            }
        }
    }
    
    // -------------------------------------------------------------------------------------------------
public:    
    static int testHarness() {
    
        string error = "";
        bool size, getElement, insert, erase, circular;
        vector<pair<bool, string>> results = {
            {size,       "size_test()"},
            {getElement, "getElement_test()"},
            {insert,     "insert_test()"},
            {erase,      "erase_test()"},
            {circular,   "makeListCircular_test()"}   
        };
    
        results[0].first = size_test(error),
        results[1].first = getElement_test(error),
        results[2].first = insert_test(error),
        results[3].first = erase_test(error),
        results[4].first = makeListCircular_test(error);    
    
        cout << "===================================\n"
             << "Unit test results for LinkedList.h:\n"
             << "===================================" 
             << endl;
        
        runTests(results, error);
        
        results[0].first = size_test(error, true),
        results[1].first = getElement_test(error, true),
        results[2].first = insert_test(error, true),
        results[3].first = erase_test(error, true),
    
        cout << "===================================\n"
             << "Unit test results for LinkedList.h:\n"
             << "       (with circular lists)       \n"   
             << "===================================" 
             << endl;
    
        runTests(results, error);
        
        return 0;
    }
};

#endif // UNITTEST_H