set term png size 720,640
set output 'del_stat.png'
set grid
set title 'Probe mean and variance in deletion'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Deletion round'
set ylabel 'mean/variance'
plot 'del_stat.csv' u 1 w lp, '' u 2 w lp, '' u 3 w lp, '' u 4 w lp, '' u 5 w lp, '' u 6 w lp
