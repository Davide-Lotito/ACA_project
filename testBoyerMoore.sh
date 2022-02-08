#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
cd ./data/
python3 remove_nl.py genome.fna 
cd ..
g++ -std=c++11 boyer_moore.cpp
./a.out ./data/genome_no_new_lines.txt ./data/pat.txt

