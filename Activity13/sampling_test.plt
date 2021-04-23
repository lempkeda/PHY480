# file: sampling_test.plt
#
# gnuplot plotfile for Monte Carlo sampling test
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
# 
#  Revision history
#   2004-05-09  original version for 780.20 session 22
#   2005-02-22  minor revisions for 780.20 session 12
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title "Energy Distributions"
set xlabel "energy E"
set ylabel "P(E)"

# set the terminal type to be the screen (which is x11 here)
set term x11 

# plot
set style data linespoints
set pointsize 2
plot \
     "sampling_test_kT10.dat" using 1:3 title 'random sampling' , \
     "sampling_test_kT10.dat" using 1:2 title 'exact T=10.', \
     "sampling_test_kT10.dat" using 1:4 title 'Metropolis T=10.' , \
     "sampling_test_kT1.dat" using 1:2 title 'exact T=1.0', \
     "sampling_test_kT1.dat" using 1:4 title 'Metropolis T=1.0'


# output the plot to the file sampling_test_plt.ps   
set out "sampling_test_plt.ps"
set term postscript color 
replot

reset
set term x11
