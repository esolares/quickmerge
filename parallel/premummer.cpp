//-------------------------------------------------------------------------------
//   Programmer: Miguel Escobar, University of California, Irvine
//         File: premummer
//         Date: 05 / 25 / 18
//
//        Usage:
//    premummer  [options]  <Reference>  <Query>
//
//      Purpose: Accelerate mummer by allowing queries to run in parrallel
//          Runs after prenuc, invokes mummer
//-------------------------------------------------------------------------------

#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <mutex> // Thread Safe Lock
#include <thread>
#include <unistd.h>

using namespace std;
//using Iter = std::vector<Query>::const_iterator;

class Query {
  public:
    std::string name;
    int length;

    Query(){}

    Query(std::string n, int l)
    {
        name = n;
        length = l;
    }

    bool operator()(Query *one, Query *two) const
    {
        return one->length < two->length; // Longest Queries have the highest priority
    }
};

class Queries { // Abstract Priority Queue to make it thread safe
  private:
    priority_queue<Query *, vector<Query *>, Query> queries;
    mutex m;

  public:
    Queries() {}

    void push(Query *q)
    {
        if (q == nullptr)
            return;

        unique_lock<mutex> lock(m);
        queries.push(q);
    }

    Query *pop()
    {
        Query *q = nullptr;

        unique_lock<mutex> lock(m); // unlocks when is out of scope
        if (queries.empty())
            return q;

        q = queries.top();
        queries.pop();

        return q;
    }

    bool empty()
    {
        unique_lock<mutex> lock(m);
        return queries.empty();
    }
};

void doWork(Queries *qs){
    vector<string> jobs;

    while(!qs->empty()){
        Query* q = qs->pop();
        cout << "thread " << this_thread::get_id() << " working on " << q->name << " time " << q->length/1000 << endl;
        jobs.push_back((q->name));
        usleep(q->length*1000);
    }

    cout << this_thread::get_id() << " did: ";
    for (auto j : jobs){
        cout << j << ", ";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    Queries jobs;
    int thread_count = 5;

    for (int i = 0; i < 20; i++) { // Populate the Job Queries
        string name;
        name = (char)((int)'a' + i);
        int delay = (rand() % 2000) + 1000;

        cout << name << ": " << delay/1000 << endl;
        Query* q = new Query(name, delay);

        jobs.push(q);
    }

    /* Spawn `m` threads to work on `n` queries*/
    // 2. Run parrallelized version of mummer, merge mpags file after complete 
    thread workers[thread_count];
    for (int i = 0; i < thread_count; i++){
        workers[i] = thread(doWork, &jobs);
    }

    /* Wait for all threads to finish running*/
    for (int i = 0; i < thread_count; i++){
        workers[i].join();
    }

    // 1. Get the output args form prenuc, add number of threads to the cli
    //-- Run prenuc and assert return value is zero
    //-- Run mummer | mgaps and assert return value is zero
    return 0;
}