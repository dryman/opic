set term png size 720,640
set output 'block_grow.png'
set grid
set title 'Block grow probability for different block size'
set datafile separator ',' 
set key autotitle columnhead
set xlabel 'Block size'
set ylabel 'Numerator of the probability (omitting 1/N)'
plot 'block_grow.csv' u 1:2 w lp, '' u 1:3 w lp, '' u 1:4 w lp
