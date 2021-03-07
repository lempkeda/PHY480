# plot file for diffeq_test_exp_back
set timestamp

set xlabel 't'
set ylabel 'y(t)'

set title 'Comparing Differential Equation Algorithms'


plot \
  "diffeq_test.dat" using ($1):(2*(abs((($2)-($4))/(($2)+($4))))) title 'Euler', \
  "diffeq_test.dat" using ($1):(2*(abs((($3)-($4))/(($3)+($4))))) title '4th order Runge-Kutta', \
  "diffeq_test_h.01.dat" using ($1):(2*(abs((($2)-($4))/(($2)+($4))))) title 'Euler h = 0.01', \
  "diffeq_test_h.01.dat" using ($1):(2*(abs((($3)-($4))/(($3)+($4))))) title '4th order Runge-Kutta h = 0.01', \
