#!/bin/bash

#for i in 128 144 160 176 192 208 224 240 256
for i in 500 550 600 650 700 750 800 850 900 950 1000
do

	make MAX_DIM=$i
	sudo likwid-perfctr -C S0:0 -g TLB_DATA -m ./arr_avg_bin > runs/run$i.out

done

#for i in 128 144 160 176 192 208 224 240 256
for i in 500 550 600 650 700 750 800 850 900 950 1000
do
	echo $i
	cat runs/run$i.out | grep "L1 DTLB load misses"
	echo ''
	echo ''

done
