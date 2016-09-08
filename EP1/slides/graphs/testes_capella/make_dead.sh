#!/bin/bash
for i in 4 8; do
	for j in 10 100 500; do
		C=result/deadlines-r$i-$j
	    python3 deadlines.py r$i $j $i > $C
	    gnuplot -e "file='$C'" deadlines.gp
	done
done