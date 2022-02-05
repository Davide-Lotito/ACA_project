#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
cd ./data/
python3 remove_nl.py genome.fna 
cd ..
g++ rabin_karp.cpp
./a.out ./data/genome_no_new_lines.txt ./data/pat.txt

