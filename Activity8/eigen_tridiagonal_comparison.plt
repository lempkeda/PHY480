# plot file for comparing eigen_tridiagonal results from GSL and Armadillo
set timestamp

set xlabel 'r'
set ylabel 'u(r)'

set title 'Comparing eigen\_tridiagonal results'

set term x11  # or alternative
plot \
  "eigen_tridiagonal.dat" using ($1):($2) title 'GSL' with lines, \
  "eigen_tridiagonal_armadillo.dat" using ($1):(-($2)) title 'Armadillo' with lines

set out "eigen_tridiagonal_comparison.ps"
set term postscript color enhanced
replot  