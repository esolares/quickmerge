//-------------------------------------------------------------------------------
//   Programmer: Miguel Escobar, University of California, Irvine
//         File: premummer
//         Date: 05 / 25 / 18
//
//        Usage:
//    $mt_mummer $num_threads algo_path $algo $mdir -l $size -n $pfx.ntref $qry_file $mgaps_path -l $clus -s $gap -d $ddiff -f $dfrac $pfx.mgaps
// 
//    Note: Order of input matters for the fasta and mgaps files
// 
//      Purpose: Accelerate mummer by allowing queries to run in parrallel
//          Runs after prenuc, invokes mummer
//-------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <unordered_map>
#include <unistd.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

// -- User Defined Libs
#include "fasta.h"
#include "query.h"
#include "queries.h"
#include "args.h"

using namespace std;

/*
    USAGE:
    $mt_mummer $num_threads algo_path $algo $mdir -l $size -n $pfx.ntref $qry_file $mgaps_path -l $clus -s $gap -d $ddiff -f $dfrac $pfx.mgaps

    Perl:
    #my $mt_mummer = "$mt_mummer_path $num_threads $algo_path $algo $mdir -l $size -n $pfx.ntref $qry_file | $mgaps_path -l $clus -s $gap -d $ddiff -f $dfrac > $pfx.mgaps";
    $mt_mummer_path $num_threads $algo_path $algo $mdir -l $size -n $pfx.ntref $qry_file $mgaps_path -l $clus -s $gap -d $ddiff -f $dfrac $pfx.mgaps

    Example:
    ./parallel/mt_mummer 5 /home/miguel/Desktop/quickmerge/MUMmer3.23/mummer -mumreference -b -l 100 -n myprefix.ntref /home/miguel/Desktop/quickmerge/sample-data/ecoli1.fasta
    /home/miguel/Desktop/quickmerge/MUMmer3.23/mgaps -l 65 -s 90 -d 5 -f .12 myprefix.mgaps
*/

void doWork(Queries *qs){
    vector<string> jobs;

    while(!qs->empty()){
        Query* q = qs->pop();
        //cout << "thread " << this_thread::get_id() << " working on " << q->fname << " time " << q->length/1000 << endl;
        jobs.push_back((q->fname));
        cout << "THREAD: " << q->cmd << " END " << endl;
        const char *command = q->cmd.c_str();
        system(command);
    }

    cout << this_thread::get_id() << " did: ";
    for (auto j : jobs){
        cout << j << ", ";
    }
    cout << endl;
}

// Write each fasta header stream to it's own fasta file
void seperateFastaQuery(string fastaIn, string fastaOut, string header, pair<streampos, streampos> pair ){
    ifstream infile;
    ofstream outfile;

    infile.open(fastaIn);
    if(!infile){
        cout<<"Failed to open file: "<< fastaIn << endl; 
        return;
    }

    outfile.open(fastaOut);

    // Read from pair.first to pair.second in fastaIn
    char c;
    infile.seekg(pair.first);
    outfile << ">" << header << endl;
    while(infile.tellg() != pair.second + (streampos) 1){
        c = infile.get();
        // Write into fastaOut
        if (c != ' ' and c != '\n'){
            outfile << c;
        }
    }
    outfile << endl;

    infile.close();
    outfile.close();
}

// Getting fasta information
void getFastaInfo( string filename, fastaReader reader, Queries *jobs, Args* arg){
    //unordered_map<string, pair<streampos, streampos> > &m
    vector<string> keys(reader.mark.size());

    unordered_map<string , pair<streampos, streampos> > m = reader.mark;
    int qNum = 1;
    for (unordered_map<string , pair<streampos, streampos> >::iterator it = m.begin();  
        it != m.end(); it++){
            string header = it->first;
            
            // Params for Query
            pair<streampos, streampos> pair = it->second;
            
            int length = pair.second - pair.first; // Get length of the query sequence
            int bLength = filename.find_last_of(".") - filename.find_last_of("/");
            string body = filename.substr( filename.find_last_of("/")+1, bLength-1); // Get body for filename

            string fasta = arg->workingPath + "/temp/fasta/" + body + "_q" + to_string(qNum) + ".fasta";
            string mgaps = arg->workingPath + "/temp/mgaps/" + body + "_q" + to_string(qNum) + ".mgaps";

            seperateFastaQuery(filename, fasta, header, pair); // Put each query into its own file
            //cout << fname << endl;
            //cout << header << ": (" << pair.first << ", " << pair.second << ") " << length << endl;

            // Create a new Query and push it onto the Priority Queue
            Query* job = new Query(fasta, length);
            job->mgaps = mgaps;
            job->cmd = arg->makeCommand(fasta, mgaps);
            jobs->push(job);

            cout << job->cmd << endl;
            qNum++;
    }
}

void createTmpPath(Args* arg){
    string path = arg->workingPath + "/temp";
    string tmp = ("mkdir -p " + path);
    string fasta = ("mkdir -p " + tmp + "/fasta/");
    string mgaps = ("mkdir -p " + tmp + "/mgaps/");
    system(tmp.c_str());
    system(fasta.c_str());    
    system(mgaps.c_str());
}

void removeTempFiles(Args* arg){
    string cmd = arg->workingPath + "/parallel/";
    string c1 = "exec rm " + cmd + "temp/fasta/*"; 
    string c2 = "exec rm " + cmd + "temp/mgaps/*"; 
    system(c1.c_str());
    system(c2.c_str());
}

void concatMgaps(Args* arg){
    string cwd = arg->workingPath + "/parallel/temp/mgaps/*.mgaps";
    string dest = arg->workingPath + "/" + arg->mgaps;
    string command = ("cat " + cwd +" > " + dest);
    const char* cmd = command.c_str();
    cout << "CONCAT: " << command << endl;
    system(cmd);
}

int main(int argc, char **argv) {
    Queries jobs;
    Args cargs;

    // Check number of argumets given
    if(cargs.checkArgLength(argc) < 0){
        cout << "ERROR: Not enough arguments." << endl;
        cout << "USAGE: " << endl;
        cout << "$mt_mummer $num_threads $algo_path $algo $mdir -l $size -n $pfx.ntref $qry_file $mgaps_path -l $clus -s $gap -d $ddiff -f $dfrac $pfx.mgaps" << endl;
        return -1;
    }

    // Parses the number of threads, fasta, and mgaps args from the command line args 
    cargs.parseArgs(argc, argv);

    // Load the fasta file and seperate queries into own fasta files
    // ASUMPTION: fasta files are already cleaned of white space
    if(cargs.fasta.empty()){
        cout << "ERROR: fasta file not specified." << endl;
        return -1;
    }
    fastaReader fReader(cargs.fasta);

    // Itterate though unordered map and save each fasta header into its own file
    // Places each fasta query into Query obj and puts the queries in Queries Priority Queue
    createTmpPath(&cargs);
    getFastaInfo(cargs.fasta, fReader, &jobs, &cargs);

    /* Spawn `m` threads to work on `n` queries*/
    // 2. Run parrallelized version of mummer, merge mpags file after complete 
    int thread_count = cargs.num_threads;

    // Limit the number of threads spawned
    if( jobs.size() < thread_count ){
        cout << "Cannot spawn " << thread_count << " threads when there is only " << jobs.size() << " queries. " << endl; 
        cout << "Program will continue with " << jobs.size() << " threads." << endl;
        thread_count = jobs.size();
    }

    // Spawn the threads to process each query
    thread workers[thread_count];
    for (int i = 0; i < thread_count; i++){
        workers[i] = thread(doWork, &jobs);
    }

    // Wait for all threads to finish running
    for (int i = 0; i < thread_count; i++){
        workers[i].join();
    } 

    // Concat All of the temp mgaps files
    concatMgaps(&cargs);

    //removeTempFiles(&cargs);

    // Let User call postnuc manually 
    return 0;
}