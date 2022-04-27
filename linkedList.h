// Copyright Jonathan Carlson 2022

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream> 
using namespace std;

#include "node.h"

template<typename T>
class LinkedList {
public:

    LinkedList() {}

    T* head = NULL;

    // ---------------------------------------------------------------------------------------------

    void printList(const T* node) {
        cout << node->value << endl;
        if(node->after)
            printList(node->after);
    }

    // ---------------------------------------------------------------------------------------------

    void printList() {
        if(head) printList(head);
    }

    // ---------------------------------------------------------------------------------------------

    void verifyIndex(int index, string functionName) {
        if(index < 0 || index > size()) {
            cout << "ERROR: Out of range index - 'LinkedList::" << functionName                                          << "(" << to_string(index) << ")'" << endl; 
            exit(139);
        } 
    }

    // ---------------------------------------------------------------------------------------------

    int size(const T* node) {
        int i = 1;
        if(node->after)
            i += size(node->after);
        return i;
    }

    // ---------------------------------------------------------------------------------------------

    int size() {
        if(head) return size(head);
        return 0;
    }

    // ---------------------------------------------------------------------------------------------

    T* getElement(int index, T* node) {
        verifyIndex(index, "getElement");
        
        if(index) {
            if(node->after)
                node = getElement(--index, node->after);
        }

        return node;
    }

    // ---------------------------------------------------------------------------------------------

    T* getElement(int index) {
        return getElement(index, head);
    }

    // ---------------------------------------------------------------------------------------------

    void insert(T* newNode, int index) {
        if(index < 0 || index > size()) {
            cout << "ERROR: Out of range index - 'LinkedList::insert(" << to_string(index) << ")'" 
                 << endl; 
            exit(139);
        } 
        
        // Insert into empty list
        if(!this->head) {
            this->head = newNode;
            return;
        }

        // Append to end of list
        if(index == size()) {
            T* node = getElement(index - 1);
            newNode->before = node;
            node->after = newNode;
            return;
        }

        T* node = getElement(index);

        if(node->before) {
            newNode->before = node->before;
            node->before->after = newNode;
        } else
            // Insert as first item in list
            this->head = newNode;
        
        newNode->after = node;
        node->before = newNode;
    }

    // ---------------------------------------------------------------------------------------------

    void push_back(T* node) {
        insert(node, size());
    }

    // ---------------------------------------------------------------------------------------------

    void erase(int index) {
        verifyIndex(index, "erase");
        
        T* node = getElement(index);
        
        if(node->before)
            node->before->after = node->after;
            
        if(node->after)
            node->after->before = node->before;
        
        if(!node->before && node->after)    
            this->head = node->after;
        
        node->after = NULL;
        node->before = NULL;
        delete node;
    }

    // ---------------------------------------------------------------------------------------------

    void loopList() {
        Node* tail = getElement(size() - 1);
        head->before = tail;
        tail->after = head;
    }
};

#endif // LINKEDLIST_H