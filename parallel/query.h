// Created by Miguel Escobar
#ifndef QUERY_H
#define QUERY_H

#include <string> 
class Query {
public:     
    std::string fname;
    std::string mgaps;
    std::string cmd;
    int length;
    Query();
    Query(std::string n, int l);
    bool operator()(Query *one, Query *two) const;
};
#endif