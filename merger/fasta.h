//
// Created by Khalid Elassaad on 10/22/17.
//

#ifndef QUICKMERGE_FASTA_H
#define QUICKMERGE_FASTA_H

#include<fstream>
#include<map>
#include<string.h>
#include<unordered_map>

class fastaReader
{
public:
    //constructors
    //fastaReader(); //Not sure if you need this line or not -Khalid
    fastaReader(std::string filename);
    //destructor
    ~fastaReader(){};
    std::map<std::string, std::pair<std::streampos, std::streampos> > mark;
};

#endif //QUICKMERGE_FASTA_H
