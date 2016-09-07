set terminal png transparent nocrop enhanced size 1000,700 font "arial,8" 
set output 'histograms.4.png'
unset key

set grid layerdefault   lt 0 linewidth 0.500,  lt 0 linewidth 0.500

set title "Immigration from Northern Europe\n(columstacked histogram)" 
set xlabel "Country of Origin" 
set ylabel "Immigration by decade" 
set palette defined ( 0 0.05 0.05 0.2, 0.1 0 0 1, 0.25 0.7 0.85 0.9,\
     0.4 0 0.75 0, 0.5 1 1 0, 0.7 1 0 0, 0.9 0.6 0.6 0.6,\
     1 0.95 0.95 0.95 )
unset ytics
set cbrange [ -1.0 : * ]
unset colorbox

set xtics 1

plot "out3c" using (($4+$3)/2):1:(($4-$3)/2):(0.48):2 with boxxy lc pal z fs solid, "out2c" using (($4+$3)/2):($1+5):(($4-$3)/2):(0.48):2 with boxxy lc pal z fs solid, "out1c" using (($4+$3)/2):($1+10):(($4-$3)/2):(0.48):2 with boxxy lc pal z fs solid


