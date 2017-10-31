//
// Created by Khalid Elassaad on 10/31/17.
//

#ifndef QUICKMERGE_DOUBLEHEADEDLINKEDLIST_H
#define QUICKMERGE_DOUBLEHEADEDLINKEDLIST_H
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
    bool isLEmpty() const;
    bool isREmpty() const;
    bool isBothEmpty() const;
    int getLSize() const;
    int getRSize() const;
    int getBothSize() const;
    string printNode(LinkedListNode*) const;
    string getLHead() const;
    string getRHead() const;
    //const LinkedListNode& front const
    void addToLHead(const std::string&, const double&, const double&);
    void addToRHead(const std::string&, const double&, const double&);
    void removeFromLHead();
    void removeFromRHead();
    LinkedListNode* getLNext();
    LinkedListNode* getRNext();
    string printLList();
    string printRList();
    string printBothList();

private:
    LinkedListNode* Lhead;
    LinkedListNode* Rhead;
    int Lsize;
    int Rsize;
    LinkedListNode* Lpointer;
    LinkedListNode* Rpointer;
};
#endif QUICKMERGE_DOUBLEHEADEDLINKEDLIST_H
