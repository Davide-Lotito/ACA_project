#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
clear
rm ./a.out
cd ./data/
python3 remove_nl.py genome.fna 
cd ..
mpic++ -std=c++11 -fpermissive ./parallel2.cpp
mpiexec -n 16 --oversubscribe ./a.out ./data/genome_no_new_lines.txt ./data/pat.txt  
