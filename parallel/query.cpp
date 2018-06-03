#include "query.h"
using namespace std;

Query::Query(){}

Query::Query(string n, int l)
{
    fname = n;
    length = l;
}

bool Query::operator()(Query *one, Query *two) const
{
    return one->length < two->length; // Longest Queries have the highest priority
}