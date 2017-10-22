//
// Created by Khalid Elassaad on 10/22/17.
//

#ifndef QUICKMERGE_FILEREADER_H
#define QUICKMERGE_FILEREADER_H

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cmath>

#include <sstream>
#include <iomanip>
#include "Alignment.cpp"

class fileReader
{
public:
    //constructors
    //fileReader(); //Again, don't know if this line is needed or not -Khalid
    fileReader(std::string fileName, double minPid, long minThreshold);
    //destructor
    ~fileReader(){};

    std::string fileName;
    double minPid;				//the double will only accept an alignment with a min pctid.
    long minThreshold;			//only accept alignments of a min length
    Alignment *alignment;

};


#endif //QUICKMERGE_FILEREADER_H
