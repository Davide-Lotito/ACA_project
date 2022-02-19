#!/bin/bash
mpirun --hostfile ../parallel/hostfile -np $1 ./a.out $2  ../../data/pat.txt    
