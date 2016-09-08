#gnuplot -e "file='deadline_r8_10'" deadlines.gp
set terminal png transparent nocrop enhanced size 1200,800 font "arial,8" 
set output file.'.png'

set boxwidth 0.25
set xrange [-0.5:4.5]
set yrange [0.25:*]
set logscale y 2
set xtics ("First-Come First-Served" 1, "Shortest Remaining Time Next" 2, "Escalonamento com multiplas filas" 3)

plot file using 1:2:3 with boxerrorbars