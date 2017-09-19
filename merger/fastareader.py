#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, os, numpy


try:
    sys.argv[1]
except:
    print 'Invalid input file or input file missing'
    print 'Usage: fastatools.py filename flagnumber'
    quit()
else:
    if sys.argv[1] == '':
        inputfile = sys.argv[1]
    else:
        inputfile = sys.argv[1]
        
outdir = "contigs"

try:
    os.stat(outdir)
except:
    os.mkdir(outdir)

###start helper functions
def getreadlenghts(filelist):
    myreadlengths = list()
    filecounter = 0
    for inputfile in filelist:
        fin = open(inputfile,'r')
        readcounter = 0
        myreadlengths.append([])
        for line in fin:
            readcounter = readcounter + 1
            if(readcounter%2==0):
                myreadlengths[filecounter].append(len(line.replace('\n','')))
        filecounter = filecounter + 1
    return myreadlengths

def filterbyreadlengths(min,max,filelist):
    for inputfile in filelist:
        fout = open(inputfile.replace('.fasta','_filtered.fasta'),'w')
        counter = 0
        for line in open(inputfile,'r'):
            counter = counter + 1
            if(counter%2 == 0):
                sequence = line.replace('\n','')
                if(len(sequence) > min-1 and len(sequence) < max+1):
                    fout.write(header)
                    fout.write(sequence + '\n')
            else:
                header = line
        fout.close()

def combinefastafile(infile):
    filereader = open(infile,'r')
    counter = 0
    myreads = dict()
    totallines = sum(1 for line in filereader)
    filereader.seek(0)
    sequence = ''
    while counter < totallines:
        temp = filereader.readline().replace('\n','')
        counter = counter + 1
        if (temp[0] == '>'):
            if (counter != 1):
                myreads[header] = sequence
                sequence = ''
            header = temp[:].split('/')[0]
        else:
            if (len(sequence) == 0):
                sequence = temp[:]
            else:
                sequence = sequence + temp[:]
    return myreads

def extractuniqueheaders(infile,numofcopies):
    filereader = open(infile,'r')
    counter = 0
    myuniqueheaders = dict()
    totallines = sum(1 for line in filereader)
    filereader.seek(0)
    while counter < totallines:
        temp = filereader.readline().replace('\n','').split('/')[0]
        counter = counter + 1
        if (temp[0] == '>'):
            myuniqueheaders[temp] = [0]*numofcopies
    return myuniqueheaders

def extractuniqueheadersonly(infile):
    filereader = open(infile,'r')
    counter = 0
    myuniqueheaders = dict()
    totallines = sum(1 for line in filereader)
    filereader.seek(0)
    while counter < totallines:
        temp = filereader.readline().replace('\n','').split('/')[0]
        counter = counter + 1
        if (temp[0] == '>'):
            myuniqueheaders[temp] = ''
    return myuniqueheaders
    
def extractuniquereads(infile,myreads,mysdiccopy):
    filereader = open(infile,'r')
    counter = 0
    myuniqueheaders = dict()
    totallines = sum(1 for line in filereader)
    filereader.seek(0)
    while counter < totallines:
        temp = filereader.readline().replace('\n','').split('/')[0]
        counter = counter + 1
        if (temp[0] == '>'):
            if (temp.split(' ')[0] == mysdiccopy[0]):
                myuniqueheaders[temp.split(' ')[0]] = mysdiccopy[1]
            else:
                myuniqueheaders[temp] = myreads[temp]
    return myuniqueheaders
###end helper functions

##we need to pay attention to how we split the header, as different fasta files require different characters for splitting.
#modify so that if the ref or qry id are too long then only hash the min required string len that produces 0 collisions
fin = open(inputfile)
delimeter = ':'
totallines = sum(1 for line in fin)
fin = open(inputfile)
print 'opened input file'
seq_read = ''
seq_name = ''
last_pos = 0
count = 0
#print('begin for loop')
while count < totallines:
    #print('for loop executed')
    last_pos = fin.tell()
    line = fin.readline()
    count = count + 1
    if line[0:1] == '>':
        #print 'found seq_name ' + line
        seq_name = line.replace('\n','')
        ###change replace statements here depending on fasta file
        outputfile = seq_name.split(delimeter)[0].replace('>','').replace(' ','_').replace('/','_') + '.fa'
        last_pos = fin.tell()
        line = fin.readline().replace('\n','')
        count = count + 1
        #print 'begin while loop on seq ' + line
        while line[0:1] != '>' and line[0:1] != '':
            seq_read = seq_read + line
            last_pos = fin.tell()
            line = fin.readline().replace('\n','')
            count = count + 1
            #print 'while loop next at last pos ' + str(last_pos)
        #print 'while loop ended'
        if line[0:1] == '>' or line[0:1] == '':
            print 'begin writing file ' + outputfile
            fout = open(outdir + '/' + outputfile, 'w')
            #fout = open('contigs//' + outputfile, 'w')
            fout.write(str(seq_name) + '\n')
            fout.write(str(seq_read) + '\n')
            fout.close
            print outputfile
            #print len(seq_read.replace("\n",""))
            seq_name = ''
            seq_read = ''
            count = count - 1
            fin.seek(last_pos)
            print 'file written'
#fin.close()
#fout.close()
