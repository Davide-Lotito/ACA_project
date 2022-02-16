#!/bin/bash
# build and run
clear
rm a.out
g++ -pthread -std=c++11 main.cpp
./a.out ../../data/EscherichiaColi/genome.fna  ../../data/pat.txt
rm a.out