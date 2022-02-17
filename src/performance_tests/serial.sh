#!/bin/bash

rm a.out
g++ -std=c++11 ../serial/main.cpp 
./a.out $1 ../../data/pat.txt
rm a.out