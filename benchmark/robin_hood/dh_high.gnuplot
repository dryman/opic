set term png size 720,640
set output 'dh_high_load.png'
set grid
set title 'Double hashing probe histogram under high load'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Probe count'
set ylabel 'Frequency'
set logscale y
plot 'high_load.csv' u 7 w lp, '' u 8 w lp, '' u 9 w lp
