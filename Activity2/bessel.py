#  file: bessel.py 
#
#  Spherical Bessel functions via up and down recursion      
#                                                                     
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history:
#      02-Jan-2004  original version, for 780.20 Computational Physics
#
#  Notes:  
#   * compile with:  "g++ -o bessel bessel.cpp"
#   * adapted from: "Projects in Computational Physics" by Landau and Paez  
#             copyrighted by John Wiley and Sons, New York               
#             code copyrighted by RH Landau  
#   * data saved as: x y1 y2                         
#  
#************************************************************************


# global constants  
xmax = 100.0 # max of x  
xmin = 0.1 # min of x >0  
step = 0.1 # delta x  
order = 10		# order of Bessel function 
start = 50		# used for downward algorithm 

#********************************************************************
int
main ()
{
  double ans_down, ans_up

  # open an output file stream
  ofstream out ("bessel.dat")

  # step through different x values
  for (double x = xmin x <= xmax x += step)
    {
      ans_down = down (x, order, start)
      ans_up = up (x, order)

      out << fixed << setprecision (6) << setw (8) << x << " "
	<< scientific << setprecision (6)
	<< setw (13) << ans_down << " "
	<< setw (13) << ans_up 
        << endl
    }
  cout << "data stored in bessel.dat." << endl

  # close the output file
  out.close ()
  return (0)
}


#------------------------end of main program----------------------- 

# function using downward recursion  
double
down (double x, int n, int m)
{
  double j[start + 2]		# array to store Bessel functions 
  j[m + 1] = j[m] = 1.		# start with "something" (choose 1 here) 
  for (int k = m k > 0 k--)
    {
      j[k - 1] = ((2. * (double) k + 1.) / x) * j[k] - j[k + 1]  # recur. rel.
    }
  double scale = ((sin (x)) / x) / j[0]	# scale the result 
  return (j[n] * scale)
}


#------------------------------------------------------------------ 

# function using upward recursion  
double
up (double x, int n)
{
  double three = 0.
  double one = (sin (x)) / x	# start with lowest order 
  double two = (sin (x) - x * cos (x)) / (x * x)	# next order
  for (int k = 1 k < n k += 1)	# loop for order of function     
    {
      three = ((2. * k + 1.) / x) * two - one	# recurrence relation  
      one = two
      two = three
    }
  return (three)
}
