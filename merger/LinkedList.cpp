//
// Created by edgec on 8/23/2017.
//

#include <iostream>
#include "LinkedList.h"


//default constructor
LinkedList::LinkedList():head(nullptr),size(0),pointer(head) {}
//destructor
LinkedList::~LinkedList() { while(!isEmpty()) removeFromHead(); }

bool LinkedList::isEmpty() const {return head == nullptr;}
void LinkedList::removeFromHead()
{
    if(!isEmpty())
    {
        LinkedListNode *old = head;
        head = old->next;
        delete old;
        size--;
    }
}

void LinkedList::addToHead(const string& name, const double& ovlWeight, const double& pctIDWeight)
{
    LinkedListNode* newNode = new LinkedListNode(name,ovlWeight,pctIDWeight);
    if(isEmpty())
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

//returns the size of the linked list. Currently not working!
int LinkedList::getSize() const
{
    return size;
}

string LinkedList::printNode(LinkedListNode* myNode) const
{
    string tempstring;
    //LinkedListNode* myNode = head;
    tempstring.append(myNode->name);
    tempstring.append(" -> OVLWeight:");
    tempstring.append(to_string(myNode->ovlWeight));
    tempstring.append(" PCTID:");
    tempstring.append(to_string(myNode->pctidWeight));
    tempstring.append("\n");
    return tempstring;
}

//returns the head
string LinkedList::getHead() const
{
    if (isEmpty()){return "Empty!\n";}
    else {return printNode(head);}
}

//getNext element of pointer, needs work!!!
LinkedListNode* LinkedList::getNext()
{
    if (pointer != nullptr)
    {
        pointer = pointer->next;
        return pointer;
    } else
    {
        return nullptr;
    }
}

//print linkedlist
string LinkedList::printList()
{
    LinkedListNode* myPointer = head;
    string tempstring;
    if(!isEmpty()) {
        while (myPointer != nullptr) {
            tempstring.append(printNode(myPointer));
            myPointer = myPointer->next;
        }
    }
    else{tempstring = "Empty!";}
    return tempstring;
}