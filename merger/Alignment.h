//
// Created by Khalid Elassaad on 10/22/17.
//

#ifndef QUICKMERGE_ALIGNMENT_H
#define QUICKMERGE_ALIGNMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class Alignment_Data
{
public:
    //constructors
    //Alignment_Data(); // Not sure if this line is need -Khalid
    Alignment_Data(std::string label, long Rstart, long Rend, long Qstart, long Qend, int Error ,int SimError ,int negNum);
    //destructor
    ~Alignment_Data(){};


    std::string label;		//the row data, uesd as key
    //ex: 2620178 2620733 6424 6980 6 6 0
    std::string refid;
    long Rstart;
    long Rend;
    long Qstart;
    long Qend;
    int Error;
    int SimError;		//similar error
    int negNum;			//negative number ( Deletion )
    double pctid;

    void set_pctid (double pctid);
    double get_pctid();
    long get_left_most_position();
    long get_right_most_position();
    long get_rstart();
    long get_rend();
    long get_qstart();
    long get_qend();
};


class Header
{
public:
    //constructors
    //Header(); // Not sure if this line is need -Khalid
    Header(std::string header, long rlen, long qlen);
    //destructor
    ~Header(){};


    std::string header;	// rname + qname , used as key
    // ex:>000003F|arrow scf7180000001372|quiver

    std::string rname;	// ex:>000003F|arrow
    std::string qname;	// ex:scf7180000001372|quiver
    long rlen;
    long qlen;
    std::unordered_map< std::string , Alignment_Data* > dataMap;	//map sotres key and ptr pair.

    void add_alignment( std::string label, long Rstart, long Rend, long Qstart, long Qend, int Error ,int SimError ,int negNum);
    void add_alignment( std::string label, Alignment_Data* ad);
    Alignment_Data* get_alignment(std::string label);
    void remove_alignment( std::string label );
    std::string get_ref_name();
    std::string get_query_name();
    long get_rlen();
    long get_qlen();
};


class Alignment
{
public:
    //constructors
    //Alignment(); // Not sure if this line is need -Khalid
    Alignment(std::string source, std::string datatype);
    //destructor
    ~Alignment(){};

    std::string source;
    std::string datatype;
    std::unordered_map< std::string , Header* > headerMap;

    void add_header( std::string header, Header* h );
    Header* get_header( std::string header);
    void list_headers();
    void remove_header( std::string header );
};


#endif //QUICKMERGE_ALIGNMENT_H
