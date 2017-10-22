#include <iostream>
#include "Alignment.h"

using namespace std;


	//  Constructor															
Alignment_Data::Alignment_Data(string label, long Rstart, long Rend, long Qstart, long Qend, int Error ,int SimError ,int negNum){
	this->label = label;
	this->Rstart = Rstart;
	this->Rend = Rend;
	this->Qstart = Qstart;
	this->Qend = Qend;
	this->Error = Error;
	this->SimError = SimError;
	this->negNum = negNum;
}

void Alignment_Data::set_pid (double pid){
	this->pid = pid;
}

double Alignment_Data::get_pid(){
	return pid;
}

long Alignment_Data::get_left_most_position(){
	if(Rend > Rstart){
		return Rstart;
	}else{
		return Rend;
	}
}

long Alignment_Data::get_right_most_position(){
	if(Rend < Rstart){
		return Rstart;
	}else{
		return Rend;
	}
}

long Alignment_Data::get_rstart(){
	return Rstart;
}

long Alignment_Data::get_rend(){
	return Rend;
}

long Alignment_Data::get_qstart(){
	return Qstart;
}

long Alignment_Data::get_qend(){
	return Qend;
}




//constructor
Header::Header(string header, long rlen, long qlen){
	this->header = header;
	this->rlen = rlen;
	this->qlen = qlen;
}
	
// adding data by information Rstart Rend .......
void Header::add_alignment( string label, long Rstart, long Rend, long Qstart, long Qend, int Error ,int SimError ,int negNum){
	Alignment_Data *ad = new Alignment_Data(label,  Rstart, Rend,  Qstart, Qend, Error ,SimError ,negNum);
	dataMap.insert( make_pair( label, ad ) );
}

// adding data by object
void Header::add_alignment( string label, Alignment_Data* ad){
	dataMap.insert( make_pair( label, ad ) );
}

//serach data by label, return ptr of object
Alignment_Data* Header::get_alignment(string label){
	unordered_map< string , Alignment_Data* >::iterator iter = dataMap.find(label);
	if(iter != dataMap.end()){
		return iter->second;
	}
	else{
		cout<<"Do not Find alignment data: "<<label<<endl;
	}
}

//remove data from map
void Header::remove_alignment( string label ){
	unordered_map< string , Alignment_Data* >::iterator iter = dataMap.find(label);
	if (iter != dataMap.end()){
		delete iter->second;	//remove object
		dataMap.erase(iter);	//remove key in map
	}
	else{
		cout<<"Do not Find header:"<< label<<endl;
	}
}

string Header::get_ref_name(){
	return rname;
}

string Header::get_query_name(){
	return qname;
}

long Header::get_rlen(){
	return rlen;
}

long Header::get_qlen(){
	return qlen;
}







Alignment::Alignment(string source, string datatype){
	this->source = source;
	this->datatype = datatype;
}

/*
void add_header( string header, long rlen, long qlen ){
	Header head( header, rlen, qlen);
	headerMap.insert( make_pair( header , head ) );
}
*/

void Alignment::add_header( string header, Header* h ){
	headerMap.insert( make_pair( header , h ) );
	//headerMap[header] = h;								//need 	empty constructor at begin  :  Header(){}
}

Header* Alignment::get_header( string header){
	unordered_map< string , Header* >::iterator iter = headerMap.find(header);
	if(iter != headerMap.end()){
		return iter->second;
	}
	else{
		cout<<"Do not Find header: "<<header<<endl;
	}
}

void Alignment::remove_header( string header ){
	unordered_map< string , Header* >::iterator iter = headerMap.find(header);	//iterator
	if (iter != headerMap.end()){
		delete iter->second;
		headerMap.erase(iter);
	}
	else{
		cout<<"Do not Find header:"<< header<<endl;
	}
}




//  test Alignment.cpp

/*
int main(){
	
//	test Alignment_data
	Alignment_Data ad1("1 2 3 4 5 6 0",1,2,3,4,5,6,7);
	cout<<"test Alignment data:" << endl<<endl;
	cout<<"  label: " <<ad1.label<<endl;
	cout<<"  Rstart:" <<ad1.Rstart<<endl;
	cout<<"  get R: " <<ad1.get_rstart()<<endl;
	cout<<"  Rend: "  <<ad1.Rend<<endl;
	cout<<"  Qstart:" <<ad1.Qstart<<endl;
	cout<<"  Qend: "  <<ad1.Qend<<endl;
	cout<<"  error: " <<ad1.Error<<endl;
	cout<<"  negative numbers:"<<ad1.negNum<<endl<<endl<<endl;
	
	Alignment_Data ad2("11 22 33 44 55 66 00",11,22,33,44,55,66,77);
	
	
//	test Header
	Header h( ">000003F|arrow scf7180000001372|quiver" , 9085994 , 21655);
	cout<<"test Header:" << endl<<endl;
	h.add_alignment("1 2 3 4 5 6 0",1,2,3,4,5,6,7);
	h.add_alignment("11 22 33 44 55 66 00",11,22,33,44,55,66,77);
	cout<< "  get info from map:" <<h.get_alignment("1 2 3 4 5 6 0")->Rend<<endl;
	cout<< "  get info from map:" <<h.get_alignment("11 22 33 44 55 66 00")->Qstart<<endl;
	cout<<endl<<endl;
	
	
//	test Alignment
	Alignment a( "/data/users/yuanhunl/Lab/self_oneline.fa /data/users/yuanhunl/Lab/hybrid_oneline.fa" ,
				 "NUCMER" );
	cout<< "  test Alignment: "<<endl<<endl;
	cout<< "  data source: "<<a.source<<endl;
	cout<< "  data type: " <<a.datatype<<endl<<endl;
	
	Header *h1  = new Header( ">000010F|arrow scf7180000001375|quiver" ,  2187667 , 18219 );
	Alignment_Data *a1 = new Alignment_Data("8373859 8395578 21655 1 72 72 0" , 8373859, 8395578, 21655, 1, 72, 72, 15);
	
	h1->add_aglinment("8373859 8395578 21655 1 72 72 0", a1);
	a.add_header(">000010F|arrow scf7180000001375|quiver" , h1);
	a.get_header(">000010F|arrow scf7180000001375|quiver")->add_alignment("8373859 8395578 21655 1 72 72 0" , 8373859, 8395578, 21655, 1, 72, 72, 15);
	
	cout<<a.get_header(">000010F|arrow scf7180000001375|quiver")->get_alignment("8373859 8395578 21655 1 72 72 0")->Rstart<<endl;
	
	
	h1  = new Header( ">000010F|arrow scf7180000001375|quiver" ,  2187667 , 18219 );
	a1 = new Alignment_Data("8373859 8395578 21655 1 72 72 0" , 8373859, 8395578, 21655, 1, 72, 72, 15);
	h1->add_aglinment("8373859 8395578 21655 1 72 72 0", a1);
	a.add_header(">000010F|arrow scf7180000001375|quiver" , h1);
	a.get_header(">000010F|arrow scf7180000001375|quiver")->add_alignment("8373859 8395578 21655 1 72 72 0" , 8373859, 8395578, 21655, 1, 72, 72, 15);
	
	cout<<a.get_header(">000010F|arrow scf7180000001375|quiver")->get_alignment("8373859 8395578 21655 1 72 72 0")->Rstart<<endl;
	
	
	system("pause");
	return 0;
}

*/
