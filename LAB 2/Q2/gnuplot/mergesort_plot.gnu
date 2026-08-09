set terminal pngcairo size 1200,700 enhanced font 'Arial,12'
set output 'Q2/plots/mergesort_growth.png'
set title 'Merge Sort vs Modified 3-way Merge Sort'
set xlabel 'n (array size)'
set ylabel 'Time (milliseconds)'
set grid
set key top left
set datafile separator ','
plot 'Q2/csv/mergesort_data.csv' using 1:2 with linespoints lw 2 pt 7 title 'Classic Merge Sort (2-way)', 'Q2/csv/mergesort_data.csv' using 1:3 with linespoints lw 2 pt 5 title 'Modified Merge Sort (3-way)'
