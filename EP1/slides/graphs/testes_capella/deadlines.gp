#gnuplot -e "file='deadline_r8_10'" deadlines.gp
set terminal png transparent nocrop enhanced size 1200,800 font "arial,8" 
set output file.'.png'

set key inside left top vertical Right noreverse enhanced autotitle box lt black linewidth 1.000 dashtype solid
set yrange [0: 1.1]

plot file using 1:2:($2+$3):($2-$3) with yerrorlines lw 1.6 title 'First-Come First-Served', \
	"" using 1:4:($4+$5):($4-$5) with yerrorlines lw 1.6 title 'Shortest Remaining Time Next', \
	"" using 1:6:($6+$7):($6-$7) with yerrorlines lw 1.6 title 'Escalonamento com multiplas filas'