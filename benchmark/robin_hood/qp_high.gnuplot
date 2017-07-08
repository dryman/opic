set term png size 720,640
set output 'qp_high_load.png'
set grid
set title 'Quadratic Probing probe histogram under high load'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Probe count'
set ylabel 'Frequency'
set logscale y
plot 'high_load.csv' u 4 w lp, '' u 5 w lp, '' u 6 w lp
