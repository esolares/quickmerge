//
// Created by Khalid Elassaad on 10/22/17.
//

#ifndef QUICKMERGE_FASTA_H
#define QUICKMERGE_FASTA_H

#include<fstream>
#include<map>
#include<string.h>
#include<unordered_map>
#include<algorithm>

class fastaReader
{
public:
    //constructors
    //fastaReader(); //Not sure if you need this line or not -Khalid
    fastaReader(std::string filename);
    std::string remake(std::string header);
    void print_headers(); //Allows you to view contents of map
    void output_fasta(std::string filename); //Outputs contents of map into fasta file
    //destructor
    ~fastaReader(){};
    std::unordered_map<std::string, std::pair<std::streampos, std::streampos> > mark;
    std::string infile_name;
};

#endif
