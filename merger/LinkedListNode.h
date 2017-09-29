//
// Created by edgec on 8/23/2017.
//

#ifndef GRAPHTEST_LINKEDLISTNODE_H
#define GRAPHTEST_LINKEDLISTNODE_H
#include <cstddef>
#include<string>

class LinkedListNode
{
    friend class LinkedList;
public:
    //constructors
    LinkedListNode();
    LinkedListNode(std::string,double, double);
    //destructor
    ~LinkedListNode(){};
    std::string getNodeName(LinkedListNode);
    double getOVLWeight(LinkedListNode);
    double getPCTIDWeight(LinkedListNode);
    //std::ostream &operator<<(std::ostream &output, const LinkedListNode &node);
private:
    std::string name;
    double ovlWeight;
    double pctidWeight;
    LinkedListNode* next;
};
#endif //GRAPHTEST_LINKEDLISTNODE_H