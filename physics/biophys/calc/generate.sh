#/usr/bin/env gnuplot -p

set terminal eps
set grid
set format x "%.1f"
set format y "%.1f"

set output 'graph1.eps'
set xrange [0:20]
set xtics 2
plot 'data.txt' using 1:2 title 'x_1' with lines lt 7 lc 1, 'data.txt' using 1:3 title 'x_2' with lines lt 7 lc 2

set output 'graph2.eps'
set xrange [*:*]
set xtics autofreq
plot 'data.txt' using 2:3 title 'x_1 / x_2' with lines lt 7
