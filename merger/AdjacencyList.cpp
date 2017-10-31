//
// Created by edwin on 8/22/17.
//

#include <iostream>
#include "AdjacencyList.h"

//default constructor
//AdjacencyList::AdjacencyList(){}
//take in a list of keys and make them all empty new lists
AdjacencyList::AdjacencyList(const int mysize):size(mysize)
{
    myAdjList.reserve(mysize);
    //for(int i = 0; i < mysize; i++)
    //{
    //    myAdjList[i] = new LinkedList();
    //}
}

//accessors
LinkedList* AdjacencyList::getList(string index)
{
    return myAdjList[index];
}

string AdjacencyList::printList(string index)
{
    return getList(index)->printList();
}

int AdjacencyList::getSize() const
{
    return size;
}

bool AdjacencyList::isEmpty(string index)
{
    LinkedList* mylist = getList(index);
    //cout << mylist->isEmpty();
    return mylist->isEmpty();
}

//mutators
void AdjacencyList::deleteList(string index)
{
    myAdjList[index] = new LinkedList();
}