#!/bin/bash

rm serial.out
g++ -std=c++11 ../serial/main.cpp -o serial.out
./serial.out $1 ../../data/pat.txt
rm serial.out