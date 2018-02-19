#!/bin/bash
for x in {1..300}
do
mpirun --allow-run-as-root -n 4 ./a.out $(($x*100)) >> data1/data.txt
mpirun --allow-run-as-root -n 1 ./a.out $(($x*100)) >> data1/data_1_proc.txt
done
