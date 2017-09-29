//
// Created by edgec on 8/23/2017.
//

#ifndef GRAPHTEST_LINKEDLIST_H
#define GRAPHTEST_LINKEDLIST_H
#include "LinkedListNode.h"
using namespace std;

class LinkedList
{
    friend class AdjacencyList;
public:
    //constructors
    LinkedList();
    //destructor
    ~LinkedList();
    bool isEmpty() const;
    int getSize() const;
    string printNode(LinkedListNode*) const;
    string getHead() const;
    //const LinkedListNode& front const
    void addToHead(const std::string&, const double&, const double&);
    void removeFromHead();
    LinkedListNode* getNext();
    string printList();

private:
    LinkedListNode* head;
    int size;
    LinkedListNode* pointer;
};
#endif //GRAPHTEST_LINKEDLIST_H
