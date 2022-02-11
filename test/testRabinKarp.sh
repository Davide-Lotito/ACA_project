#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
clear
rm ../a.out
cd ../data/
python3 remove_nl.py genome.fna 
cd ..
g++ -std=c++11 testRabinKarp.cpp
./a.out ./data/genome_no_new_lines.txt ./data/pat.txt