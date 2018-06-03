#include "queries.h"

Queries::Queries() {}

void Queries::push(Query *q)
{
    if (q == nullptr)
        return;

    unique_lock<mutex> lock(m);
    queries.push(q);
}

Query *Queries::pop()
{
    Query *q = nullptr;

    unique_lock<mutex> lock(m); // unlocks when is out of scope
    if (queries.empty())
        return q;

    q = queries.top();
    queries.pop();

    return q;
}

bool Queries::empty()
{
    unique_lock<mutex> lock(m);
    return queries.empty();
}

int Queries::size(){
    unique_lock<mutex> lock(m);
    return queries.size();
}
