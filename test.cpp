#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Alignment.cpp"
using namespace std; 

int main(void){
	
	
	///////		 Alignment		////////
	
	//Alignment   (string rname, string qname, long rstart, long rend, long  qstart, long qend, long rlen, long qlen, long rcov, long qcov, float pid);
	Alignment alig("rname123"  ,"qname123"   ,112         ,345       , 678         , 912      , 356      , 482      , 134      , 432      , 3.5);

	cout<<"Check get_query_name: " 			<< alig.get_query_name() <<endl;
	cout<<"Check get_ref_name: "   			<< alig.get_ref_name() <<endl;
	cout<<"Check get_ref_coverage: "  		<< alig.get_ref_coverage()<<endl;
	cout<<"Check get_query_coverage: "		<< alig.get_query_coverage()<<endl;
	cout<<"Check get_percent_id: "	  		<< alig.get_percent_id()<<endl;
	cout<<"Check get_left_most_position: "  << alig.get_left_most_position()<<endl;
	cout<<"Check get_right_most_position: " << alig.get_right_most_position()<<endl;
	cout<<"Check get_rlen: " 				<< alig.get_rlen()<<endl;
	cout<<"Check get_qlen: "				<< alig.get_qlen()<<endl<<endl;
	

	
	cout<<"Check get_r_coords"<< endl;
	long coords[2] ={0};
	coords[0]=*alig.get_r_coords();
	coords[1]=*(alig.get_r_coords()+1);
	cout<<"rstart: "<<coords[0]<<endl;
	cout<<"rend: "  <<coords[1]<<endl<<endl;;
	
	cout<<"Check get_q_coords"<< endl; 
	long coords2[2] ={0};
	coords2[0]=*alig.get_q_coords();
	cout<<"qstart: "<<coords2[0]<<endl;
	coords2[1]=*(alig.get_q_coords()+1);
	cout<<"qend: "  <<coords2[1]<<endl<<endl;
	
	cout<<"Check get_r_coords_qname" << endl;
	cout<<"qname:"<< alig.get_r_coords_qname()->qname<<endl;
	cout<<"rstart"<<alig.get_r_coords_qname()->rstart<<endl;
	cout<<"rend"  <<alig.get_r_coords_qname()->rend<<endl;
	cout<<endl<<endl<<endl;
	
	
	
	///////		 Constructed_Alignment		////////
	
	//Constructed_Alignment (string rname, string qname, long rstart, long rstop, string id1, long rlen, string label);
	cout<<"Constructed_Alignment:"<<endl<<endl;
	//Constructor
	Constructed_Alignment CA( "rname"    , "qname"     , 1234       , 9461     , ""        , 345     , "ACTG");
	cout<<"Check get_ref_name: "	<< CA.get_ref_name()<<endl;
	cout<<"Check get_query_name: "	<< CA.get_query_name()<<endl;
	cout<<"Check get_label: "		<< CA.get_label()<<endl;
	cout<<"Check get_left_most_position: " << CA.get_left_most_position()<<endl;
	cout<<"Check get_right_most_position: "<< CA.get_right_most_position()<<endl;
	
	
	
	cout<<"Check get_r_coords: "<<endl;
	long coords3[2] = {0};
	coords3[0] = *CA.get_r_coords();
	coords3[1] = *(CA.get_r_coords()+1);
	cout<<"rstart: "<<coords3[0]<<endl;
	cout<<"rend: "<<coords3[1]<<endl;
	
	
	// void set_r_coords(long start,long end);
	cout<<"Check set_r_coords:"<<endl;
	CA.set_r_coords(4444,66666);
	coords3[0] = *CA.get_r_coords();
	coords3[1] = *(CA.get_r_coords()+1);
	cout<<"rstart: "<<coords3[0]<<endl;
	cout<<"rend: "<<coords3[1]<<endl;	
	
	cout<<"Check get_rlen: "	<<CA.get_rlen()<<endl;
	cout<<"Check get_arlen: "	<<CA.get_arlen()<<endl;
	cout<<"Check get_cov: " 	<<CA.get_cov()<<endl;
	
	CA.add_id("AAAA");
	CA.set_label("GGGG");
	CA.add_annotation("q2name"     ,"CCCC"     ,0.5);
	CA.add_annotation("q3name"     ,"AGTG"     ,0.7);
	CA.add_annotation("q4name"     ,"GATG"     ,0.4);
	//			     (string q2name,string label,float percent)
	
	map< string, pair<double  ,string > >::iterator iter;
	//			CA's ptr:ann_dict
	for(iter = CA.ann_dict->begin(); iter != CA.ann_dict->end(); iter++){
        cout<< iter->first <<" " <<iter->second.first <<"  " <<iter->second.second<<endl;
	} 

	
	
	
	
	
	
	return 0;
}
