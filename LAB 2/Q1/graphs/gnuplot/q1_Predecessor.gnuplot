set terminal pngcairo size 1200,700 enhanced font 'Arial,12'
set output 'Q1/plots/q1_Predecessor.png'
set title 'Q1 - Predecessor: Comparison of Data Structures'
set xlabel 'Input Size (n)'
set ylabel 'Order of Growth'
set grid
set logscale y
set key outside right
set datafile separator ','
set xtics 100
plot 'Q1/csv/q1_Predecessor.csv' using 1:2 with lines lw 2 title 'Unsorted Array', \
     'Q1/csv/q1_Predecessor.csv' using 1:3 with lines lw 2 title 'Sorted Array', \
     'Q1/csv/q1_Predecessor.csv' using 1:4 with lines lw 2 title 'Unsorted SLL', \
     'Q1/csv/q1_Predecessor.csv' using 1:5 with lines lw 2 title 'Sorted SLL', \
     'Q1/csv/q1_Predecessor.csv' using 1:6 with lines lw 2 title 'Unsorted DLL', \
     'Q1/csv/q1_Predecessor.csv' using 1:7 with lines lw 2 title 'Sorted DLL'
