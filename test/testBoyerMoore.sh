#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
clear
rm ../a.out
cd ../data/
python3 remove_nl.py ./EscherichiaColi/genome.fna
python3 remove_nl.py pat.txt 
cd ..
g++ -std=c++11 testBoyerMoore.cpp
./a.out ./data/genome_no_new_lines.txt ./data/pat.txt