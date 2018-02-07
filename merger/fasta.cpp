//FastaReader, this class will record the start line and end line of the sequence
//header will be used as the key of the map


#include <iostream>
#include "fasta.h"
#include <regex>

#define HEADER_LEN 120 
                      // Cuts headers down to this length. Is NOT max length
                      // In case of duplicates, additional characters will be
                      // added to headers, possibly taking their length past this value

using namespace std;

bool is_header_in_map(string header, const unordered_map<string, pair<streampos, streampos> > m)
{
    try
    {
        m.at(header);
        return true;
    }
    catch (out_of_range)
    {
        return false;
    }
}

bool is_numbered_header(string header) {
    // Returns true if header ends in an integer preceded by an underscore
    regex re("^.*_[0-9]+$");
    return regex_match(header, re);
}

string rename_header(string header) {
    // In case of duplicates, rename header (underscore and a number)
    if (!is_numbered_header(header)) {return header+"_2";}
    else {
        string str_int = "";
        int j = header.length() - 1; //Index of last char
        while (header[j] != '_') {
            str_int = header[j] + str_int;
            j--;
            header.pop_back();
        }
        str_int = to_string(atoi(str_int.c_str()) + 1);
        return header+str_int;
    }
}

void save_in_map(string header, streampos start, streampos end,
        unordered_map<string, pair<streampos, streampos> > &m)
{
    bool duplicate = is_header_in_map(header, m);
    string orig = header;
    while (is_header_in_map(header, m)) {
        header = rename_header(header);
    }
    if (duplicate) {
        cout << "Header '"<<orig<<" already present in map" << endl;
        cout << "\tRenaming header for sequence from "<<start<<" to "<<end
            <<" as "<< header<<endl;
    }
    m[header].first = start;
    m[header].second = end;
    return;
}

string fix_header(string header) {
    // Replace invalid characters
    // Cuts header length to a max length
    while (header.length() > HEADER_LEN) {
        header.pop_back();
    }

    //Break at '|' or ' '
    size_t found = header.find(' ');
    while (found!=string::npos) {
        header.pop_back();
        found = header.find(' ');
    }
    found = header.find('|');
    while (found!=string::npos) {
        header.pop_back();
        found = header.find('|');
    }

    char s[HEADER_LEN + 1];
    char replace_chars[32] = "\\/,*=(){}[]'\";?:-%$&@#^`~\t<>";

    strcpy(s, header.c_str());

    char *temp = strpbrk(s, replace_chars);
    while (temp) {
        *temp = '_';
        temp = strpbrk(s, replace_chars);
    }

    int max_len = HEADER_LEN;
    char *p = s;

    while (max_len > 0) {
        max_len--;
        p++;
    }
    *p = '\0';
    return s;
}

void advance_to_beginning(ifstream &fp) {
    // puts file pointer at first char of sequence
    char c = fp.get();
    while (c == '\r' or c == '\n') {
        c = fp.get();
    }
    fp.seekg(fp.tellg() - (streampos) 1);
    return;
}

string read_header(ifstream &fp) {
    // For now, this reads the raw header and returns it as a string, while incrementing
    // the streampos counter.
    string retstring = "";
    char c = fp.get();
    // if first char isn't '>', fail
    if (c != '>') {cout << "First char must be '>' for a valid header" << endl; exit(1);}

    //advance one more (We don't want the bracket to be saved)
    c = fp.get();

    while (c != '\n' and c != '\r') {
        retstring.append(1,c);
        c = fp.get();
    }
    advance_to_beginning(fp);
    retstring = fix_header(retstring);
    return retstring; 
}


int advance_to_end(ifstream &fp) {
    //puts file pointer at last character of sequence
    char c = fp.get(); //first char of sequence
    streampos currpos;

    if (c == '>') {cout << "First char in sequence must not be '>'" << endl; exit(1);}

    while (c != '>' and c != EOF) { //Stop if c is one of these two chars
        currpos = fp.tellg();
        c = fp.get();
    }
    if (c == EOF) {
        return 1;
    }
    //Now we are at the header, step back 1 char to be at the '>'
    //This allows for safe loop into read_header
    fp.seekg(fp.tellg() - (streampos) 1);
    return 0;
}


streampos get_end_of_last_sequence(ifstream &fp, int eof_check)
{
    //This function starts at either the end of file, or the '>' of the next header.
    //It steps back to the end of last sequence, returns that position, but keeps
    //the fp stream pointed at the same char
    streampos retpos;
    streampos original_pos = fp.tellg();
    char c;
    if (eof_check) {
        fp.clear();
    }
    fp.seekg(fp.tellg() - (streampos) 1);
    c = fp.get();
    while (c == '\r' or c == '\n' or c == ' ')
    {
        fp.seekg(fp.tellg() - (streampos) 2);
        c = fp.get();
    }
    retpos = fp.tellg() - (streampos) 1;
    fp.seekg(original_pos);
    return retpos;
}


fastaReader::fastaReader(string filename) {
    // Filepointer to the file initialized
    ifstream fp(filename, ifstream::in | ios::binary);

    // Check if file opens successfully
    if (!fp) {cout<<"Failed to open file: "<<filename<<endl; return;}

    // Declare necessary variables
    string header = "";
    streampos pos = fp.tellg();
    streampos start;
    streampos end;
    char cbuff;
    int eof_check = 0;

    // Remember that the hashmap is initialized in the header file
    // unordered_map<string, pair<streampos, streampos>> mark
    
    // Start the reading procedure
    //      1 - Read the header
    //      2 - Advance to beginning of sequence
    //      3 - Save pos1
    //      4 - Advance to end of sequence
    //      5 - Save pos2
    //      6 - Save header, pos1, pos2 in map
    //      7 - Repeat or terminate

    while (!eof_check)
    {
        header = fix_header(read_header(fp)); //Step 1, 2 - fp at start of sequence

        start = fp.tellg(); //Step 3

        eof_check = advance_to_end(fp); //Step 4 - Returns 1 if EOF, 0 if on another '>'

        end = get_end_of_last_sequence(fp, eof_check); //Step 5

        save_in_map(header, start, end, mark);
        /* TESTING PURPOSES
        fp.clear();
        pos = fp.tellg();
        cout << header << endl;
        cout << "Regex Match: " << is_numbered_header(header) << endl;
        cout << start;
        fp.seekg(start);
        cbuff = fp.get();
        cout << cbuff << endl;
        cout << end;
        fp.seekg(end);
        cbuff = fp.get();
        cout << cbuff << endl;
        fp.seekg(pos);
        */
    }
    /*
    cout << endl << "Header Map Contents:" << endl;
    typedef unordered_map<string, pair<streampos, streampos> >::const_iterator MapIterator;
    for (MapIterator iter = mark.begin(); iter != mark.end(); iter++)
    {
            cout << "\tHeader: " << iter->first << endl;
            cout << "\tStart :" << iter->second.first << endl;
            cout << "\tEnd   :" << iter->second.second << endl;
    }*/
} 

/*
int main(int argc, char* argv[]) {
    fastaReader f(argv[1]);
    cout << "Successful termination" << endl;
    return 0;
}*/

// UNCOMMENT ALL THESE COMMENT BLOCKS FOR TESTING PURPOSES
// Love, Khalid
