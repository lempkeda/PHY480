# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'n points'
set ylabel 'Relative error'

set title 'Comparing Integration Routines'


plot \
  "integrate.dat" using ($1):($2) title 'Simpson', \
  "integrate.dat" using ($1):($3) title 'Milne', \
  "integrate.dat" using ($1):($4) title 'GSL QAG 31', \
  
