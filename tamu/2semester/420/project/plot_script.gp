reset
set term png
set term png size 1024, 768
set output 'image_plot.png'

# color definitions
set border linewidth .5
set style line 1 lc rgb '#19194d' lt 1 lw 2 pt 7 pi -1 ps 1
set style line 2 lc rgb '#09094d' lt 1 lw 2 pt 7 pi -1 ps 1
set pointintervalbox 1

# unset key

# set xrange [0:5]
# set yrange [0:4]

set multiplot layout 1, 2 ;
set title "Score";
plot 'data.txt' using 1 title 'Score' with linespoints ls 1

set title "Bit Score";
plot 'data.txt' using 2 title 'Bit Score' with linespoints ls 2 
unset multiplot
