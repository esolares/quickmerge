
nucmer takes two fasta file
- one if the reference
- other is the query

What does a fasta with multiple queries look like?
- diff headers and seq on same file
- no overlap

Make a program that is after `prenuc`
- Ecapsultate `Mummer`
- Take in the fasta file
    1. Break into queries (Different Sequences)
        - Call `fileReader.cpp`
    2.  Run `n` threads to handle all queries
        - Each thread will invoke `Mummer` library 
        - Each thread will pop from the queries QUEUE
        - QUEUE should be proiritized by length (Longest job first)
        - What does Mummer output? MGAPS Files?
    3. Merge MGAPS Files
        - Concat them?