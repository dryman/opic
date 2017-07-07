set term png size 720,640
set output 'lp_high_load.png'
set grid
set title 'Linear Probing probe histogram under high load'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Probe count'
set ylabel 'Frequency'
set logscale y
plot 'high_load.csv' u 1 w lp, '' u 2 w lp, '' u 3 w lp
