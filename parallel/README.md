# Multithreaded Mummer 
## mt_mummer

- Purpose: Multithread mummer to execute multiple queries in parallel
1. Queries are extracted from a given fasta file and seperated into their own temporary fasta files
2. Files are then put into a priority queue where longest queries get executed first
3. Each temp query gets executed via system call to mummer where it is then fed to mgaps
4. Each of the respective mgaps files are then concatenated into one large mgaps file specified by the user

- Example usage:
- 2nd argument specifies number of threads to be spawn
- Fasta file is the query 
- Mgaps is the final output file

## USAGE
```bash
./parallel/mt_mummer 4 /home/user/Desktop/quickmerge/MUMmer3.23/mummer -mumreference -b -l 100 -n myprefix.ntref /home/user/Desktop/quickmerge/sample-data/ecoli1.fasta /home/user/Desktop/quickmerge/MUMmer3.23/mgaps -l 65 -s 90 -d 5 -f .12 myprefix.mgaps
```
---

## What is happening behind the scenes
1. When called form root quickmerge folder
```bash
./parallel/mt_mummer 4 /home/user/Desktop/quickmerge/MUMmer3.23/mummer -mumreference -b -l 100 -n myprefix.ntref /home/user/Desktop/quickmerge/sample-data/ecoli1.fasta /home/user/Desktop/quickmerge/MUMmer3.23/mgaps -l 65 -s 90 -d 5 -f .12 myprefix.mgaps
```
2. For every query qi.fasta > qi.mgaps
- n threads are spawned to execute m queries (m threads max)
- temporary files are stored in temp/fasta and temp/mgaps
```
/home/user/Desktop/quickmerge/MUMmer3.23/mummer -mumreference -b -l 100 -n myprefix.ntref /home/user/Desktop/quickmerge/parallel/temp/fasta/ecoli1_qi.fasta | /home/user/Desktop/quickmerge/MUMmer3.23/mgaps -l 65 -s 90 -d 5 -f .12  > /home/user/Desktop/quickmerge/parallel/temp/mgaps/ecoli1_qi.mgaps
```
3. Concatenating the mgaps files
```bash
cat /home/user/Desktop/quickmerge/parallel/temp/mgaps/*.mgaps > /home/user/Desktop/quickmerge/myprefix.mgaps
```

4. Clean up removing the temp files 
- In mt_mummer.cpp main
```c++
removeTempFiles(&cargs)
```
- Removing Temp Files
```bash
rm /home/user/Desktop/quickmerge/parallel/temp/fasta/*
rm /home/user/Desktop/quickmerge/parallel/temp/mgaps/*
```

## Integrating into nucmer.pl
- Replace Step 2,3 (Current Mummer) with these binaries
- Must create `$mt_mummer_path` and `$num_threads` within script
```perl
#my $mt_mummer = "$mt_mummer_path $num_threads $algo_path $algo $mdir -l $size -n $pfx.ntref $qry_file $mgaps_path -l $clus -s $gap -d $ddiff -f $dfrac $pfx.mgaps"
system($mt_mummer);
```