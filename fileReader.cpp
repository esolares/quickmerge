#include<iostream>
#include<fstream>
#include<map>
#include <unordered_map>
	
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cmath>

#include <sstream>
#include <iomanip>
#include "Alignment.cpp"
using namespace std;

class fileReader {
				
	public:
		string fileName;
		double minPid;				//the double will only accept an alignment with a min pctid.
		long minThreshold;			//only accept alignments of a min length
		Alignment *alignment;
		
		//	Constructor	 //
		fileReader(string fileName, double minPid, long minThreshold){
			//				         minimumPID, minimumThresholds
			// deal with the input data
			this->fileName = fileName;
			this->minPid = minPid;
			this->minThreshold = minThreshold;
			
			/////////      file reader	
    		char outDelta[128] ;        		//array for file name
    		strcpy(outDelta, fileName.c_str()); //copy the input filename to outDelta
    		fstream fp;							//file ptr
    		char line[128];						//array for reading a line
    		fp.open(outDelta, ios::in);			//open file
    		
    		if(!fp){       						//reading error
        		cout<<"Fail to open file: "<<outDelta<<endl;
    		}
    		

    		//////////     Create Alignment Object
    		fp.getline(line, sizeof(line), '\n');	//the first line
    		string dataSource( line );
    		fp.getline(line, sizeof(line), '\n');	//the second line
    		string dataType( line );
    		///////////////////
    		//				 //
			//	 Alignment   //
			//				 //
    		///////////////////
    		//Alignment alignment( dataSource, dataType);
			alignment = new Alignment(dataSource, dataType); 
    		
    		cout<<"Data source: "<<alignment->source<<endl;
    		cout<<"Data type: "<<alignment->datatype<<endl;
    		system("pause");
    		
    		
    		
    		
    		
    		
			fp.getline(line, sizeof(line), '\n');
			////////////////////
			//				  //
			//  find heaader  //
			//				  //
			////////////////////
			while(line[0]=='>'){	
				
				// Read header and split the data
										   //these is a split function
  				const char *sep = " "; //define the char to split
  				char *p;			   //used to store the substring
  				p = strtok(line , sep);
  				string rname =p;
  				cout<<"Rname is: "<<rname<<endl;
  				
    			p = strtok(NULL, sep);
    			string qname = p;
    			cout<<"Qname is: "<<qname<<endl;
  				
  				p = strtok(NULL, sep);
   				string rlenString = p;
   				long rlen = atol( rlenString.c_str() );
				cout<<"rlen is: "<<rlen<<endl;
					   					
    			p = strtok(NULL, sep);					
    			string qlenString = p;
    			long qlen = atol( qlenString.c_str() );
  				cout<<"qlen is: "<<qlen<<endl;
 
										
				//create header
				Header *h = new Header( rname + " " + qname, rlen, qlen );	//store the data into header
					//Header h( rname + " " + qname, rlen, qlen );
				
				fp.getline(line, sizeof(line), '\n');	//move to next line
					
				//check if it is alignment data
				int spaceCounter = 0;			//alignment data has 6 space in a line, insertnio and deletion string does not
				for(int i = 0; i<strlen( line ); i++){
					if(line[i]==' ')
						spaceCounter++;
					if(spaceCounter>=2)
						break;
				}
				///////////////////////////
				//				  		 //
				//  read alignment data  //
				//				  		 //
				///////////////////////////			
				while( spaceCounter > 0){
					string label = (line);
					long Rstart = 0;
					long Rend = 0;
					long Qstart = 0;
					long Qend = 0;
					int error = 0;
					int simError = 0;
					int negative = 0;
					double pid = 0;
					
					//split the line, get data
					cout<<"Alignment data: "<<line<<endl;
					cout<<"label: " << label << endl;
 	 				const char *sep = " "; //define the char to split
  					char *p;			   //used to store the substring
  					p = strtok(line , sep);
  					string temp =p;
  					Rstart = atol( temp.c_str() );
  					cout<<"Rstart is: "<<Rstart<<endl;					

  					p = strtok(NULL , sep);
  				    temp =p;
  					Rend = atol( temp.c_str() );
  					cout<<"Rend is: "<<Rend<<endl;		

  					p = strtok(NULL , sep);
  					temp =p;
  					Qstart = atol( temp.c_str() );
  					cout<<"Qstart is: "<<Qstart<<endl;		
					  
  					p = strtok(NULL , sep);
  					temp =p;
  					Qend = atol( temp.c_str() );
  					cout<<"Qend is: "<<Qend<<endl;		
					  
  					p = strtok(NULL , sep);
  					temp =p;
  					error = atol( temp.c_str() );
  					cout<<"Error is: "<<error<<endl;		
					  
					p = strtok(NULL , sep);
  					temp =p;
  					simError = atol( temp.c_str() );
  					cout<<"simError is: "<<simError<<endl;							

					
						
					/////////////////////////////////////////
					//   								   //
					//   read insertion deletion string	   //
					//									   //
					/////////////////////////////////////////
					fp.getline(line, sizeof(line), '\n');	//move to next line
					while( line[0] != '0'){
						//cout<<line<<endl;
						
						//count deletion
						if( atoi(line) < 0){
							negative++;
						}
						fp.getline(line, sizeof(line), '\n');	//move to next line
					}
					
						
					//calculate pid
					pid = (double)(Rend - Rstart + 1 - error + negative) / ( Rend - Rstart + 1 + negative);
					cout<<"PID is : " << pid<<endl;
					
					// judge the alignment_data
					long RefLength = abs(Rstart - Rend + 1);
					if( pid >= minPid && RefLength>=minThreshold ){

						//create alignemnt_data obj
						Alignment_Data *Ad = new Alignment_Data( label, Rstart, Rend, Qstart, Qend, error, simError, negative);//create an obj and ptr
						Ad->set_pid(pid);
							
							
						//Alignment_Data Ad( label, Rstart, Rend, Qstart, Qend, error, simError, negative); //thid will create an obj
							
						
						//map into header
						h->add_aglinment( label, Ad);
						
						
					}
					
					
					
					// find next alignment data
						
					fp.getline(line, sizeof(line), '\n');	//move to next line
					if(line[0]=='>'){
						cout<<endl<<endl;
						break;
					}
					spaceCounter = 0;	
					for(int i = 0; i<strlen( line ); i++){
						if(line[i]==' ')
							spaceCounter++;
						if(spaceCounter>=2)
							break;
					}
				}	// end alignment data
				
					
				//map header into Alignment obj
				string temps = rname + " " + qname;		//the first parameter can not be daynamic input
				alignment->add_header( temps , h);		//so we need to use temps to store it
					


			}
    			
    		fp.close();
    		
    		
		}	//end constructor
		
		

		
		
		
		
			
};



/* 

int main(void){
	
	fileReader FR("outdelta.txt" , 0, 0.0 );
	cout<<endl;
	cout<<"fileName: "<<FR.fileName<<endl;
	cout<<"min Pid "<<FR.minPid<<endl;
	cout<<"min Threshhold:" <<FR.minThreshold<<endl;
	
	//check storing data
	cout<<FR.alignment->get_header(">000003F|arrow scf7180000001372|quiver")->get_alignment("8373859 8395578 21655 1 72 72 0")->Rend<<endl;
	//check get_pid
	cout<<FR.alignment->get_header(">000003F|arrow scf7180000001372|quiver")->get_alignment("8373859 8395578 21655 1 72 72 0")->get_pid()<<endl;
	//check get R coord
	cout<<FR.alignment->get_header(">000003F|arrow scf7180000001372|quiver")->get_alignment("8373859 8395578 21655 1 72 72 0")->get_rstart()<<endl;
	
	system("pause");
	return 0;
}

*/ 
