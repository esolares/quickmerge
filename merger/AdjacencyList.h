//
// Created by edwin on 8/22/17.
//

#ifndef GRAPHTEST_ADJACENCYLIST_H
#define GRAPHTEST_ADJACENCYLIST_H

#include <vector>
#include <unordered_map>
#include "LinkedList.h"
using namespace std;

class AdjacencyList
{
public:
    //constructors
    //AdjacencyList();
    AdjacencyList(const int);
    //destructors
    ~AdjacencyList();

    //fxns
    //accessor
    LinkedList* getList(string index);
    string printList(string index);
    int getSize() const;
    bool isEmpty(string);

    //mutator
    void setList();
    void deleteList(string);

private:
    const int size;
    unordered_map<string,bool> visited;
    unordered_map<string,LinkedList*> myAdjList;
};
#endif //GRAPHTEST_ADJACENCYLIST_H