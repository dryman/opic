set term png size 720,640
set output 'rhh_vs_qp.png'
set grid
set title 'Quadratic Probing with and without robin hood heuristic'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Probe count'
set ylabel 'Frequency'
set logscale y
plot 'rhh_vs_qp.csv' u 1 w lp, '' u 2 w lp
