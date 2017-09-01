#include <iostream>
#include <string>
#include<vector>
#include <map>
using namespace std; 

// r_coords_qname
class RCQ {
public:
	long rstart;
	long rend;
	string qname;
};

class Alignment {
public:
	//Constructor
	Alignment(string rname, string qname, long rstart, long rend, long  qstart, long qend, long rlen, long qlen, long rcov, long qcov, float pid);
	
	void str();			//the description of this function is comment out
	
	//method
	string get_ref_name();
	string get_query_name();
	long   get_ref_coverage();
	long   get_query_coverage();
	float  get_percent_id();
	
	long   get_left_most_position();
	long   get_right_most_position();
	
	long*  get_r_coords();			//This function will save the rstart and rend into coords[]
	long   coords[2];				//and then return the ptr of coords[]
	
	long*  get_q_coords();			//This function will save the qstart and qend into coords2[]
	long   coords2[2];				//and then return the ptr of coords2[]
	
	long   get_rlen();
	long   get_qlen();
	
	RCQ*   get_r_coords_qname();

	//	  Variable	//
	string rname;
	
	RCQ *rcq;
	//string qname;
	//long  rstart;
	//long  rend;
	
	long  rlen;
	long  rcov;
	long  qstart;
	long  qend;
	long  qlen;
	long  qcov;
	float pid;
	
};

Alignment::Alignment(string rname, string qname, long rstart, long rend, long qstart, long qend, 
					 long rlen, long qlen, long rcov,long qcov, float pid){
		
		rcq = new RCQ();
		rcq->qname  = qname;
		rcq->rstart = rstart;
		rcq->rend   = rend;
		//this->qname  = qname;
		//this->rstart = rstart;
		//this->rend   = rend;
	
		this->rname  = rname;
		this->qstart = qstart;
		this->qend   = qend;  			//for sam data, stores the qalen since information of the query is not given
		this->rlen   = rlen;
		this->qlen   = qlen;
		this->rcov   = rcov;
		this->qcov   = qcov;
		this->pid    = pid;				// for sam data, this value stores the MapQ, not the pid since the pid is calculated differently depending on the version of SAM used
	
}

/*
//Original:
def __str__(self):
	return "{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\n".format(self.rname, self.qname, self.rstart, self.rend, self.qstart, self.qend, self.rlen, self.qlen, self.rcov, self.qcov, self.pid)

// translation:
void Alignment::str(){
	cout << rname << "\t" << qname << "\t" << rstart << "\t" << rend << "\t" << qstart << "\t" << qend << "rlen" << qlen << "\t" << rcov << "\t" << qcov << "\t" << pid << endl;
}
*/

string Alignment::get_ref_name(){
	return rname;
}

string Alignment::get_query_name(){
	return rcq->qname;
}

long Alignment::get_ref_coverage(){
	return rcov;
}

long Alignment::get_query_coverage(){
	return qcov;
}

float Alignment::get_percent_id(){
	return pid;
}

long Alignment::get_left_most_position(){
	if(rcq->rend > rcq->rstart){
		return rcq->rstart;
	}else{
		return rcq->rend;
	}
}

long Alignment::get_right_most_position(){
	if(rcq->rend < rcq->rstart){
		return rcq->rstart;
	}else{
		return rcq->rend;
	}
}

long* Alignment::get_r_coords(){
	coords[0] = rcq->rstart;
	coords[1] = rcq->rend;
	return coords;
}


RCQ* Alignment::get_r_coords_qname(){

	return rcq;
}

long* Alignment::get_q_coords(){
	coords2[0] = qstart;
	coords2[1] = qend;
	return coords2;
}
long Alignment::get_rlen(){
	return rlen;
}
long Alignment::get_qlen(){
	return qlen;
}









//////////////////////////////////		Constructed_Alignment			//////////////////////////////////

class Constructed_Alignment{

public:
	//constructor
	Constructed_Alignment(string rname, string qname, long rstart, long rstop, string id1, long rlen, string label);		
	
	//method
	string get_ref_name();
	string get_query_name();
	string get_label();
//	string get_ann_dict();
	
	long   get_left_most_position();
	long   get_right_most_position();
	
	long*  get_r_coords();
	long   coords[2];
	
	void   set_r_coords(long start,long end);
	long   get_rlen();
	long   get_arlen();
	double   get_cov();
	
	void   add_id(string id);
	void   set_label(string new_label);
	void   add_annotation(string q2name,string label,double percent);
	map< string, pair<double  ,string > >* get_ann_dict();

		
	//variable
	string rname;
	string qname;
	string label;
	
	long   rstart;
	long   rstop;
	long   rlen;
	long   arlen;
	double  cov;
	
	vector<string> id_list;
//	map< string qname, pair<float pcov ,string annotation_label> p> ann_dict;
	map< string ,pair<double  ,string > >* ann_dict;
};

//Constructor 
Constructed_Alignment::Constructed_Alignment(string rname, string qname, long rstart, long rstop, string id1, long rlen, string label){
		this->rname = rname;
		this->qname = qname;
		this->rstart= rstart;
		this->rstop = rstop;
		this->arlen = rstop - rstart; 	// the alignment length of the reference sequence
		this->rlen  = rlen;
		this->cov   = (arlen*1.0)/(rlen*1.0);
		this->label = label;
		id_list.push_back(id1);			// list of queries that are part of this merged alignment
		this->ann_dict = new map< string , pair<double  ,string > >();
		//this->ann_dict = dict(); 		// dictionary of { qname : (pcov, annotation_label) }       no need in c++
}

/*
//in Python:
	def __repr__(self):
		if self.label == "UAR" or self.label == "UAQ":
			return "{}\t{}\t{}\t{}\t{}\n".format(self.rname, self.qname, self.rstart, self.rstop, self.label)   
		else:
			return_str = ""
			base_str = "{}\t{}\t{}\t{}".format(self.rname, self.qname, self.rstart, self.rstop)
			for ann_q, pct_label in  self.ann_dict.items():
				return_str += base_str + "\t" + ann_q + "\t" + str(pct_label[1]) + "\t" + str(pct_label[0]) + "\n"
			return return_str   
			
//in C++
Constructed_Alignment::repr(){
	if(label== "UAR" || label == "UAQ"){
		cout << rname << "\t" << qname << "\t" << rstart << "\t" << rstop << "\t" << label << endl; 
	}
	else{
		
	}
}
*/
string Constructed_Alignment::get_ref_name(){
	return rname;
}
string Constructed_Alignment::get_query_name(){
	return qname;
}
long Constructed_Alignment::get_left_most_position(){
	if(rstop > rstart){
		return rstart;
	}else{
		return rstop;
	}
}

long Constructed_Alignment::get_right_most_position(){
	if(rstop < rstart){
		return rstart;
	}else{
		return rstop;
	}
}

/////////////////////////////////////////////
long* Constructed_Alignment::get_r_coords(){
	coords[0]=rstart;
	coords[1]=rstop;
	return coords;
}
void Constructed_Alignment::set_r_coords(long start,long end){
		rstart = start;
		rstop = end;
		this->arlen = rstop - rstart;
}
void Constructed_Alignment::add_id(string id){
	id_list.push_back(id);
}

void Constructed_Alignment::add_annotation(string q2name,string label,double percent){
	this->ann_dict->insert(make_pair(q2name,  make_pair(percent,label)) );   //[q2name]  = pair<float ,string>(percent, label); 
	
}


long Constructed_Alignment::get_rlen(){
	return rlen;
}
long Constructed_Alignment::get_arlen(){
	return arlen;
}
double Constructed_Alignment::get_cov(){
	return cov;
}
void Constructed_Alignment::set_label( string new_label){
	label = new_label;
}
string Constructed_Alignment::get_label(){
	return label;
}
	
//get_ann_dict
map< string , pair<double ,string > >* Constructed_Alignment::get_ann_dict(){
	return this->ann_dict;
}

/*
// test
int main(void){
	//Alignment   (string rname, string qname, long rstart, long rend, long  qstart, long qend, long rlen, long qlen, long rcov, long qcov, float pid);
	Alignment alig("rname","qname",112, 345, 678, 912, 356, 482, 134, 432, 3.5);
	string name1 = alig.get_query_name();
	string name2 = alig.get_ref_name();
	cout<<"Check get_query_name: " << name1 <<endl;
	cout<<"Check get_ref_name: " << name2 <<endl;
	
	Constructed_Alignment a("c", "d", 12, 23, "e", 34, "f");
	map< string , pair<float  ,string > > *b;
	b = a.get_ann_dict();
	return 0;
}


*/








