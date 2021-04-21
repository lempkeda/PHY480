# file: mc_integration.plt
#
# gnuplot plotfile for monte carlo integratoin
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
# 
#  Revision history
#   2004-03-05  original version for 780.20 session 12
#   2016-03-29  fixed logscale and sprintf for newer versions of gnuplot
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title "Monte Carlo Integration"
set xlabel "# of integration vectors"
set ylabel "absolute error"

# fit to the logarithms of the data
f(x) = m*x + b
fit [1:8] f(x) "mc_integration.dat" using (log10($1)):(log10(abs($2-$3)/$3)) via m,b


# set the terminal type to be the screen (which is x11 here)
set term x11
 
# add label with fitted slope
unset label   # clear old labels
set label sprintf("fit slope = %-+4.2f", m) at graph 0.75,0.80

# do a log-log plot
set logscale xy

# plot
plot "mc_integration.dat" using ($1):(abs($2-$3)/$3) title "monte carlo estimate" ,\
 10**b*x**m title "best-fit line"

# output the plot to the file mc_integration_plt.ps   
set out "mc_integration_plt.ps"
set term postscript 
replot
