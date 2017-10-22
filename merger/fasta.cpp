//FastaReader, this class will record the start line and end line of the sequence
//header will be used as the key of the map


#include<iostream>
#include "fasta.h"


using namespace std;


fastaReader::fastaReader( string filename){

	ifstream fp(filename, ifstream::in | ios::binary);
	char line[128];
	//fp.open(filename, ios::in);// open file

	if(!fp){	//if fail to open the file
		cout<<"Fail to open file: "<<filename<<endl;
	}


	string prev = "";	//string to save previous line
	string header = "";
	string tempS = "";	//temp string
	streampos pos = fp.tellg();		//stream position
	streampos pos2;					//previous stram position
	streampos start;				//start of the seq
	streampos end;					//end of the seq

	//map<string, pair<streampos, streampos>> mark;	//bookmark

	while(fp.getline(line, sizeof(line), '\n')){

		//if found header (start with '>')
		if (line[0] == '>'){

			//record the end of the seq
			if(prev != "")
				end = pos2;
			//hash into map
			if(header!=""){
				mark[header] = make_pair(start, end);		//store into map
			}

			//record the header and start pos of seq
			tempS = line;
			start = fp.tellg();


			//////////////////////////
			//					    //
			//   parse the header   //
			//					    //
			//////////////////////////
			//this section can filt out the useless symbol and store the clean header
			char s[256];
			strcpy(s, tempS.c_str());

			const char *del = " ,*=/_\t";
			char *p;
			p = strtok(s,del);

			cout << " get header: " <<endl<<p <<endl;
			//p=strtok(NULL,d);

			header = p;

		}

		prev = line;
		//cout<<pos<<" " <<line<<endl;
		pos2 = pos;
		pos = fp.tellg();	//move the position ptr
	}

	fp.clear();									//clear the fp ptr, because the state flag of fp was -1.
	fp.seekg(0, fp.end);						//move to the end of the file
	//need to do one more time since there are no header to trigger mapping
	mark[header].first = start;
	mark[header].second = pos2;   				//record the end of the last line.


	fp.close();//close file
	}




/*

//test fastaReader
int main(){
	
	fastaReader f("test2.txt");
	
	///////////////////////
	//					 //
	//   check the map	 //
	//					 //
	///////////////////////
    cout<<endl<<"check mark:"<<endl<<endl;
    
    ifstream fp("test2.txt", ifstream::in | ios::binary);
    char line[128];
    
    for (auto it = f.mark.begin(); it != f.mark.end(); it++){
    	
    	cout << "header: " << it->first <<endl << " start: " << it->second.first << " " << "end: "<<it->second.second << endl;
    	//cout << " length of line: " << it->first.length() <<endl;
    	
    	//	check start position
    	fp.seekg(it->second.first);		//start of the header
   		fp.getline(line, sizeof(line), '\n');
   		cout<< " check the start position: " <<endl;
   		cout<< " " <<line << endl;
   		
    	//check end position
    	cout << " check the end position: "<<endl;
    	fp.seekg(it->second.second);
    	fp.getline(line, sizeof(line), '\n');
    	cout << " "<< line << endl;
    	
    	cout<<endl;
	}
    
    system("pause");
    return 0;
}

*/

