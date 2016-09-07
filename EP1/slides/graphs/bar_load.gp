set terminal png transparent nocrop enhanced size 1200,800 font "arial,8" 
set output 'histograms.4.png'
# set terminal latex
# set output "eg1.tex"

unset key

set grid layerdefault   lt 0 linewidth 0.500,  lt 0 linewidth 0.500

set xlabel "segundos" 
set ylabel "Escalonadores" 
set palette defined ( 0 0.05 0.05 0.2, 0.1 0 0 1, 0.25 0.7 0.85 0.9,\
     0.4 0 0.75 0, 0.5 1 1 0, 0.7 1 0 0, 0.9 0.6 0.6 0.6,\
     1 0.95 0.95 0.95 )
unset ytics
set cbrange [ -1.0 : * ]
unset colorbox

set xtics 0.5
set ytics ("MUFI" 1.5, "STRF" 6.5, "FCFS" 11.5)

plot "out3c" using (($4+$3)/2):1:(($4-$3)/2):(0.48):2 with boxxy lc pal z fs solid, \
	'' using (($4+$3)/2):1:2 with labels font "Helvetica,7" tc ls 1 notitle, \
	"out2c" using (($4+$3)/2):($1+5):(($4-$3)/2):(0.48):2 with boxxy lc pal z fs solid, \
	'' using (($4+$3)/2):($1+5):2 with labels font "Helvetica,7" tc ls 1 notitle, \
	"out1c" using (($4+$3)/2):($1+10):(($4-$3)/2):(0.48):2 with boxxy lc pal z fs solid, \
	'' using (($4+$3)/2):($1+10):2 with labels font "Helvetica,7" tc ls 1 notitle


