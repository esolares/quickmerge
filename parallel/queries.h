// Created by Miguel Escobar
#ifndef QUERIES_H
#define QUERIES_H

#include <queue>
#include <vector>
#include <mutex> // Thread Safe Lock
#include <string>
#include "query.h"
using namespace std;

class Queries { // Abstract Priority Queue to make it thread safe
  private:
    priority_queue<Query *, vector<Query *>, Query> queries;
    mutex m;
  public:
    Queries();
    void push(Query *q);
    Query *pop();
    bool empty();
    int size();
};

#endif