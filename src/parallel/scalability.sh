#!/bin/bash
# clear
#rm a.out
#mpic++ -std=c++11 main.cpp
mpiexec  -np  $1 ./a.out $2  ../../data/pat.txt    