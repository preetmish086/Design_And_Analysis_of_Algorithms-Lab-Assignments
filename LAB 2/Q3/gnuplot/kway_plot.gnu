set terminal pngcairo size 1200,700 enhanced font 'Arial,12'
set output 'Q3/plots/kway_growth.png'
set title 'Merging k Sorted Arrays (each of size n=200)'
set xlabel 'k (number of arrays)'
set ylabel 'Time (milliseconds)'
set grid
set key top left
set datafile separator ','
plot 'Q3/csv/kway_data.csv' using 1:2 with linespoints lw 2 pt 7 title 'Method 1: Sequential O(nk^2)', 'Q3/csv/kway_data.csv' using 1:3 with linespoints lw 2 pt 5 title 'Method 2: Pairwise O(nk log k)'
