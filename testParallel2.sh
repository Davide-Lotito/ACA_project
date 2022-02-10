#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
rm ./a.out
cd ./data/
python3 remove_nl.py genome.fna 
cd ..
mpic++ -std=c++11 ./parallel2.cpp
mpirun ./a.out ./data/genome_no_new_lines.txt ./data/pat.txt