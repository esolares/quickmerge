//
// Created by Khalid Elassaad on 10/31/17.
//


#include <iostream>
#include "DoubleHeadedLinkedList.h"


//default constructor
LinkedList::LinkedList():Lhead(nullptr),Rhead(nullptr),Lsize(0),Rsize(0),Lpointer(Lhead),Rpointer(Rhead) {}
//destructor
LinkedList::~LinkedList() {
    while(!isLEmpty()) removeFromLHead();
    while(!isREmpty()) removeFromRHead();
}

bool LinkedList::isLEmpty() const {return Lhead == nullptr;}
bool LinkedList::isREmpty() const {return Rhead == nullptr;}
bool LinkedList::isBothEmpty() const {return isLEmpty() and isREmpty();}

void LinkedList::removeFromLHead()
{
    if(!isLEmpty())
    {
        LinkedListNode *old = Lhead;
        Lhead = old->next;
        delete old;
        Lsize--;
    }
}

void LinkedList::removeFromRHead()
{
    if(!isREmpty())
    {
        LinkedListNode *old = Rhead;
        Rhead = old->next;
        delete old;
        Rsize--;
    }
}

void LinkedList::addToLHead(const string& name, const double& ovlWeight, const double& pctIDWeight)
{
    LinkedListNode* newNode = new LinkedListNode(name,ovlWeight,pctIDWeight);
    if(isLEmpty())
    {
        Lhead = newNode;
    }
    else
    {
        newNode->next = Lhead;
        Lhead = newNode;
    }
    Lsize++;
}

void LinkedList::addToRHead(const string& name, const double& ovlWeight, const double& pctIDWeight)
{
    LinkedListNode* newNode = new LinkedListNode(name,ovlWeight,pctIDWeight);
    if(isREmpty())
    {
        Rhead = newNode;
    }
    else
    {
        newNode->next = Rhead;
        Rhead = newNode;
    }
    Rsize++;
}
//Ignore next comment?
//returns the size of the linked list. Currently not working!
int LinkedList::getLSize() const
{
    return Lsize;
}

int LinkedList::getRSize() const
{
    return Rsize;
}

int LinkedList::getBothSize() const
{
    return Lsize+Rsize;
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

//returns the Lhead
string LinkedList::getLHead() const
{
    if (isLEmpty()){return "Empty!\n";}
    else {return printNode(Lhead);}
}
//returns the Rhead
string LinkedList::getRHead() const
{
    if (isREmpty()){return "Empty!\n";}
    else {return printNode(Rhead);}
}

//getNext element of pointer, needs work!!!
LinkedListNode* LinkedList::getLNext()
{
    if (Lpointer != nullptr)
    {
        Lpointer = Lpointer->next;
        return Lpointer;
    } else
    {
        return nullptr;
    }
}

LinkedListNode* LinkedList::getRNext()
{
    if (Rpointer != nullptr)
    {
        Rpointer = Rpointer->next;
        return Rpointer;
    } else
    {
        return nullptr;
    }
}

//print linkedlist
string LinkedList::printLList()
{
    LinkedListNode* myPointer = Lhead;
    string tempstring;
    tempstring.append("Left list:\n");
    if(!isLEmpty()) {
        while (myPointer != nullptr) {
            tempstring.append(printNode(myPointer));
            myPointer = myPointer->next;
        }
    }
    else{tempstring = "Empty!";}
    return tempstring;
}

string LinkedList::printRList()
{
    LinkedListNode* myPointer = Rhead;
    string tempstring;
    tempstring.append("Right list:\n");
    if(!isREmpty()) {
        while (myPointer != nullptr) {
            tempstring.append(printNode(myPointer));
            myPointer = myPointer->next;
        }
    }
    else{tempstring = "Empty!";}
    return tempstring;
}

string LinkedList::printBothList()
{
    string tempstring;
    tempstring.append(printLList());
    tempstring.append(printRList());
    return tempstring;
}