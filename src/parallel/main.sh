#!/bin/bash
# build and run
clear
rm a.out
mpic++ -std=c++11 main.cpp
mpiexec -n 16 --oversubscribe ./a.out ../../data/EscherichiaColi/genome.fna  ../../data/pat.txt
# mpiexec -n $1  ./a.out ../../data/EscherichiaColi/genome.fna  ../../data/pat.txt
rm a.out