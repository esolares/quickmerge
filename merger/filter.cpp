//This filter can clean up the fasta file, get rid of the symbol that are useless

#include <iostream>
#include "filter.h"

using namespace std;
 
int main(){
	//input file
    char filename[]="test2.txt";
    ifstream fin(filename, ifstream::in);
    //output file
	string filename2 = "output.txt";
	ofstream fout(filename2.c_str(), ofstream::out);
    char line[128];

    if(!fin){
        cout<<"Fail to open file: "<<filename<<endl;
    }
    
    /*
    while(fp.getline(line, sizeof(line))){
		fp2 << line << endl;
	}
	*/
	string l;

	while (!fin.eof()){
		fin >> l;	//read a line from input file
		//cout << l << endl;	//chech this line
		
		
		//if (!isalpha(l[l.length() - 1]))
		//	cout << int(l[l.length() - 1])<< endl;
		
		char s[256];
		if(l[0]=='>'){
			fout << endl;
			
			//remove the redundant info of header
			fin.getline(line, sizeof(line), '\n');
	
			//filt the header
			strcpy(s, l.c_str());
			const char *del = " ,*=/_\t";
			char *p;
			p = strtok(s,del);
			cout<<p<<endl;
			//l = p;
			fout<<p;
			fout<<endl;
		}
		//write to output file
		else{
			fout << l;
		}
		l="";
	}
 
    fin.close();
    fout.close();
    system("pause");
    return 0;
}

