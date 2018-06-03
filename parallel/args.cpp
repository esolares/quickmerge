#include "args.h"

Args::Args(){}

// Lazy Parsing of arguments
void Args::parseArgs(int argC, char **argV ){

    argc = argC;
    argv = argV;

    // Number of threads to run the program
    num_threads = stoi(argV[1]) ; 

    // Save the input fasta and the output mgaps
    for(int i = 2; i < argc; i++){
        string arg = argv[i];
        if(arg.substr(arg.find_last_of(".")+1) == "fasta"){
            fasta = arg;
        }
        else if(arg.substr(arg.find_last_of(".")+1) == "mgaps"){
            mgaps = arg;
        }
    }
    
    char resolved_path[PATH_MAX]; 
    realpath(".", resolved_path); 
    workingPath = resolved_path;
    //workingPath += "/parallel";
}

int Args::checkArgLength(int argc){
    if(argc < 2){
        return -1;
    }
    return 0;
}

// | operator will appear after .fasta position
// > operator will appear before last argument
// ./mt_mummer ... ecoli.fata | mgaps ... > prefix.mgaps
string Args::makeCommand(string newFasta, string mgaps){
    string command = "";
    
    for(int i = 2; i < argc; i++){
        
        string arg = argv[i];
        if(arg.substr(arg.find_last_of(".")+1) == "mgaps"){ // Put > before .mgaps
            command += " > "+ mgaps + " ";
            continue;
        }
        
        if(arg.substr(arg.find_last_of(".")+1) == "fasta"){   // Put | after .fasta
            command += newFasta + " | ";
            continue;
        }

        command += arg;
        command += " ";
    }

    return command;
}