set term png size 720,640
set output 'worst_case.png'
set style data histogram
set style histogram cluster gap 2
set style fill solid border -1
set boxwidth 0.9
set title "Worst case performance analysis on Quadratic Probing\nwith and without Robin Hood Hashing heuristic"
set datafile separator ',' 
set key autotitle columnhead
set auto x
set xtic rotate by -45 scale 0
set ylabel 'OP/s throughput'
set y2label 'Average probe count'
set yrange [0:50000000]
set y2range [0:20]
set ytics 10000000 nomirror
set y2tics 1 nomirror

plot 'worst_case.csv' u 2:xticlabels(1) ti col axes x1y2, \
  '' u 4 ti col axes x1y2, \
  '' u 3 with lp ti col axes x1y1, \
  '' u 5 with lp ti col axes x1y1

