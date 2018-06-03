#ifndef ARGS_H
#define ARGS_H

#include <queue>
#include <vector>
#include <mutex> // Thread Safe Lock
#include <string>
#include <linux/limits.h> // WATCHOUT for this dependency
// Created by Miguel Escobar
#include "query.h"
using namespace std;

class Args {
  public:
    int argc; // from main
    char ** argv; // from main
    string fasta; // fasta filename
    string mgaps; // mgaps file name
    string workingPath; // cwd for the executed file
    int num_threads; // num of threads from the argv 

    Args();
    void parseArgs(int argC, char **argV );
    int checkArgLength(int argc);
    string makeCommand(string newFasta, string mgaps);
};

#endif