//  file: bessel.cpp 
//
//  Spherical Bessel functions via up and down recursion      
//                                                                     
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2011  new version, for 780.20 Computational Physics
//	16-Feb-2021  Dave Lempke's new and improved version with relative error
//
//  Notes:  
//	I do not have any expericen with bessel functions so I am really not sure how to analyze the regions of the plot
//	I produced, or even if the plot is correct. It seems like genenerally, both of these methods are very innacurate
//	except for around certain values. For low x (below 10), both methods are entirely innacurate from the gsl function
//	and good accuracy is only found in higher values starting around x= 18. Even then it seems that both methods only
//	become accurate around very specific values (multiples of pi???). Even then slopes are not predictable ex. around
//	x = 30 there seems to be a smooth dip towrd accuracy when it is usually fairly sharp. Only then in higher values above 50
//	does it seem that the up recursion method becomes superior. This is most likely due to subtractive error with the down method
//	but I am not sure as I really don't even know what a bessel function is.                      
//  
//	What is happening on the plot that shows relative difference between the up and down recursion methods is much more clear. 
//	There is very little difference between the two methods between x=10 and x=30. From either side of this range the error between
//	the two increases to a very high power relationship. from 1 to 10 there is a 16 order of magnitude decrease in relative error between 
//	the two. I dont know what the reason would be for such a high power relationship. 
//************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
#include <gsl/gsl_sf_bessel.h>

using namespace std;		// we need this when .h is omitted

// function prototypes 
double down_recursion (double x, int n, int m);	// downward algorithm 
double up_recursion (double x, int n);	        // upward algorithm 

// global constants  
const double xmax = 100.0;	// max of x  
const double xmin = 0.1;	// min of x >0  
const double step = 0.01;	// delta x  
const int order = 10;		// order of Bessel function 
const int start = 50;		// used for downward algorithm 

//********************************************************************
int
main ()
{
  double ans_down, ans_up, diff_up, diff_down, actual;

  // open an output file stream
  ofstream my_out ("bessel.dat");

  my_out << "# Spherical Bessel functions via up and down recursion" 
         << endl;

  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
      
      actual = gsl_sf_bessel_j1 (x);
      
      diff_up = (fabs(actual - ans_up) / (fabs(actual) + fabs(ans_up)));
      diff_down = (fabs(actual - ans_down) / (fabs(actual) + fabs(ans_down)));
      
      
      my_out << fixed << setprecision (12) << setw (8) << x << "  "
	<< scientific << setprecision (12)
	<< setw (13) << ans_down << "  "
	<< setw (13) << ans_up << "  "
	<< setw (13) << diff_up << "  "
	<< setw (13) << diff_down
        << endl;
    }
  cout << "data stored in bessel.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program----------------------- 

// function using downward recursion  
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions 
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here) 
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2.* double(k) + 1.) / x) * j[k] - j[k + 1];  // recur. rel.
    }
  double scale = (sin (x) / x) / j[0];	// scale the result 
  return (j[n] * scale);
}


//------------------------------------------------------------------ 

// function using upward recursion  
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order 
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function     
    { // recurrence relation
      term_three = ((2.*double(k) + 1.) / x) * term_two - term_one;	       
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}
