#!/bin/bash
for x in {1..10000}
do
#mpirun --allow-run-as-root -n 4 ./a.out $(($x*10000)) >> data.txt
mpirun --allow-run-as-root ./a.out $(($x*10000)) >> data_1_proc.txt
done
