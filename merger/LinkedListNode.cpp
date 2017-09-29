//
// Created by edgec on 8/23/2017.
//

#include <iostream>
#include "LinkedListNode.h"
using namespace std;

//default constructor
LinkedListNode::LinkedListNode(string n, double ovl, double pctid):name(n),ovlWeight(ovl),pctidWeight(pctid),next(nullptr) {}
//place destructor below

string LinkedListNode::getNodeName(LinkedListNode node) { return node.name; }
double LinkedListNode::getOVLWeight(LinkedListNode node) { return node.ovlWeight; }
double LinkedListNode::getPCTIDWeight(LinkedListNode node) { return node.ovlWeight; }