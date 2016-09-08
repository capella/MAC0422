#!/bin/bash
for i in 4 8; do
	for j in 10 100 500; do
		C=result/trocas-r$i-$j
	    python3 trocas.py r$i $j > $C
	    gnuplot -e "file='$C'" trocas.gp
	done
done