set term png size 720,640
set output 'low_load.png'
set grid
set title 'Probe histogram under low load'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Probe count'
set ylabel 'Frequency'
set logscale y
plot 'low_load.csv' u 1 w lp, '' u 2 w lp, '' u 3 w lp, '' u 4 w lp, '' u 5 w lp, '' u 6 w lp, '' u 7 w lp, '' u 8 w lp, '' u 9 w lp
