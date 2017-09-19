#include <iostream>
#include <string>
#include<vector>
#include <map>
using namespace std; 

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
	
	long*  get_r_coords();
	long   coords[2];
	
	long*  get_q_coords();
	long   coords2[2];
	
	long   get_rlen();
	long   get_qlen();
	
	//vector<long int>get_r_coords_qname();

	//	  Variable	//
	string rname;
	string qname;
	long  rstart;
	long  rend;
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
		this->rname  = rname;
		this->qname  = qname;
		this->rstart = rstart;
		this->rend   = rend;
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
	return qname;
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
	if(rend>rstart){
		return rstart;
	}else{
		return rend;
	}
}

long Alignment::get_right_most_position(){
	if(rend>rstart){
		return rstart;
	}else{
		return rend;
	}
}

long* Alignment::get_r_coords(){
	coords[0] = rstart;
	coords[1] = rend;
	return coords;
}

/*
Alignment::get_r_coords_qname(){

	//return (self.rstart,self.rend,self.qname)
}*/

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
	long   get_cov();
	
	void   add_id(string id);
	void   set_label(string new_label);
	void   add_annotation(string q2name,string label,float percent);
	map< string, pair<float  ,string > >* get_ann_dict();

		
	//variable
	string rname;
	string qname;
	string label;
	
	long   rstart;
	long   rstop;
	long   rlen;
	long   arlen;
	float  cov;
	
	vector<string> id_list;
//	map< string qname, pair<float pcov ,string annotation_label> p> ann_dict;
	map< string ,pair<float  ,string > >* ann_dict;
};

//Constructor 
Constructed_Alignment::Constructed_Alignment(string rname, string qname, long rstart, long rstop, string id1, long rlen, string label){
		this->rname = rname;
		this->qname = qname;
		this->rstart= rstart;
		this->rstop = rstop;
		this->arlen = rstop - rstart; 	// the alignment length of the reference sequence
		this->rlen  = rlen;
		this->cov   = arlen / float(rlen);
		this->label = label;
		id_list.push_back(id1);			// list of queries that are part of this merged alignment
		this->ann_dict = new map< string , pair<float  ,string > >();
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

void Constructed_Alignment::add_annotation(string q2name,string label,float percent){
	this->ann_dict->insert(make_pair(q2name,  make_pair(percent,label)) );   //[q2name]  = pair<float ,string>(percent, label); 
	
}


long Constructed_Alignment::get_rlen(){
	return rlen;
}
long Constructed_Alignment::get_arlen(){
	return arlen;
}
long Constructed_Alignment::get_cov(){
	return cov;
}
void Constructed_Alignment::set_label( string new_label){
	label = new_label;
}
string Constructed_Alignment::get_label(){
	return label;
}
	
//get_ann_dict
map< string , pair<float ,string > >* Constructed_Alignment::get_ann_dict(){
	return this->ann_dict;
}


int main(void){
	Constructed_Alignment a("c", "d", 12, 23, "e", 34, "f");
	map< string , pair<float  ,string > > *b;
	b = a.get_ann_dict();
	return 0;
}










