#!/bin/bash
# remove newlines from genome, then search genome for gene using rabin-karp.
clear
rm ../a.out
cd ../data/
# python3 remove_nl.py ./EscherichiaColi/genome.fna
python3 remove_nl.py ./NostocPunctiforme/genome.fna
python3 remove_nl.py pat.txt
cd ..
g++ -std=c++11 testRabinKarp.cpp
# g++ -pg -std=c++11 testRabinKarp.cpp -o test_grprof
./a.out ./data/genome_no_new_lines.txt ./data/pat_no_new_lines.txt
# ./test_grprof ./data/genome_no_new_lines.txt ./data/pat_no_new_lines.txt