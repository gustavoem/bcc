print uhul;
open(GPLOT, "| gnuplot") or die "ferro";
select GPLOT;
print GPLOT "plot 2*x;";
#select GPLOT; $|=1; select STDOUT;