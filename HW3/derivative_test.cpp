//  file: derivative_test.cpp
// 
//  Program to study the error in differentiation rules
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/14/04  original version, translated from derivative_test.c
//      01/20/05  modified extrap_diff to use central_diff
//
//  Notes:
//   * Based on the discussion of differentiation in Chap. 8
//      of "Computational Physics" by Landau and Paez.
//   * As a convention (advocated in "Practical C"), we'll append
//      "_ptr" to all pointers.
//   * Use the adaptive gsl_diff_central function as well.
//      Output from this with e^(-x) at x=1 is:
//  gsl_diff_central(1) = -3.6787944117560983e-01 +/- 6.208817e-04
//   actual relative error: 1.13284386e-11 
//
//*****************************************************************
// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
using namespace std;		// we need this when .h is omitted
#include <gsl/gsl_math.h>
#include <gsl/gsl_diff.h>

// function prototypes 
double funct (double x, void *params_ptr);
double funct_deriv (double x, void *params_ptr);

double forward_diff (double x, double h,
		     double (*f) (double x, void *params_ptr),
		     void *params_ptr);
double central_diff (double x, double h,
		     double (*f) (double x, void *params_ptr),
		     void *params_ptr);
double adaptive_central_diff (double x, double h,
		     double (*f) (double x, void *params_ptr),
		     void *params_ptr);         
double extrap_diff (double x, double h,
		    double (*f) (double x, void *params_ptr),
		    void *params_ptr);
double extrap_diff2 (double x, double h,
		    double (*f) (double x, void *params_ptr),
		    void *params_ptr);
//************************** main program ***************************
int
main (void)
{
  void *params_ptr;		// void pointer passed to functions 

  const double hmin = 1.e-10;	// minimum mesh size 
  double x = 1.;		// find the derivative at x 
  double alpha = 1.;		// a parameter for the function 
  double diff_cd, diff_fd;	// central, forward difference 
  double diff_extrap, diff_extrap2;		// extrapolated derivative 
  double diff_gsl_cd;		// gsl adaptive central derivative 
  gsl_function My_F;		// gsl_function type 
  double abserr;                // absolute error

  ofstream out ("derivative_test.dat");	// open the output file 

  params_ptr = &alpha;		// double to pass to function 

  double answer = funct_deriv (x, params_ptr);	// exact answer for test 

  My_F.function = &funct;	// set up the gsl function 
  My_F.params = params_ptr;
  gsl_diff_central (&My_F, x, &diff_gsl_cd, &abserr);	// gsl calculation

  cout << "gsl_diff_central(" << x << ") = " << scientific
    << setprecision (16) << diff_gsl_cd << " +/- "
    << setprecision (6) << abserr << endl;
  cout << " actual relative error: " << setprecision (8)
    << fabs ((diff_gsl_cd - answer) / answer) << endl;

  double h = 0.5;		// initialize mesh spacing 
  while (h >= hmin)
    {
      diff_fd = forward_diff (x, h, &funct, params_ptr);
      diff_cd = central_diff (x, h, &funct, params_ptr);
      diff_extrap = extrap_diff (x, h, &funct, params_ptr);
      diff_extrap2 = extrap_diff2(x, h , &funct, params_ptr);

      // print relative errors to output file 
      out << scientific << setprecision (8)
	<< log10 (h) << "   "
	<< log10 (fabs ((diff_fd - answer) / answer)) << "   "
	<< log10 (fabs ((diff_cd - answer) / answer)) << "   "
	<< log10 (fabs ((diff_extrap - answer) / answer)) << "   "
    << log10 (fabs ((diff_extrap2 - answer) / answer)) << endl;

      h /= 2.;		// reduce mesh by 2 
    }
  cout << "ADATIVE FOUND H VALUE: " << log10 (adaptive_central_diff (x, .5, &funct, params_ptr)) << endl;
  out.close ();         // close the output stream
  return (0);		// successful completion 
}

//************************** funct ***************************
double
funct (double x, void *params_ptr)
{
  double alpha;
  alpha = *(double *) params_ptr;

  return (exp (-alpha * x));
}

//************************** funct_deriv *********************
double
funct_deriv (double x, void *params_ptr)
{
  double alpha = *(double *) params_ptr;

  return (-alpha * exp (-alpha * x));
}

//************************** forward_diff *********************
double
forward_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (f (x + h, params_ptr) - f (x, params_ptr)) / h;
}

//************************** central_diff *********************
double
central_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (f (x + h / 2., params_ptr) - f (x - h / 2., params_ptr)) / h;
}


// My adaptive method here relies on the assumption that as h decreases, difference between two
// tests of central_diff will only increase after the ideal h value is reached.
// I really wasn't sure this was going to work but it works very well here
double
adaptive_central_diff (double x, double h,
        double (*f) (double x, void *params_ptr), void *params_ptr)
{
  double new_test, old_test, old_difference, new_difference;
  int conseq_difference_changes = 0;
  
  old_test = central_diff (x, h, f, params_ptr); // setting the inital values for these before the while loop
  h = h/1.2;                                     // 1.2 here can be changed depending on the accuracy desired
  new_test = central_diff (x, h, f, params_ptr);
  old_difference = fabs(new_test - old_test);
  old_test = new_test;
  
  while(conseq_difference_changes < 2){   // the number 2 here can be changed and but for this case, 2 is fine
    h = h/1.2;
    new_test = central_diff (x, h, f, params_ptr);
    new_difference = fabs(new_test - old_test);
    if(new_difference > old_difference){    
      conseq_difference_changes++;
    }
    old_test = new_test;                  // set the old values for another iteration through
    old_difference = new_difference;
  }
  return h;                               // returning the h value
}
//************************** extrap_diff *********************
double
extrap_diff (double x, double h,
	     double (*f) (double x, void *params_ptr), void *params_ptr)
{
  
  return (8. * (f (x + h / 4., params_ptr) - f (x - h / 4., params_ptr))
	  - (f (x + h / 2., params_ptr) -
	     f (x - h / 2., params_ptr))) / (3. * h);
  
  //return ( 4.*central_diff (x, h/2., f, params_ptr) -
  //            central_diff (x, h, f, params_ptr) ) / 3.;	     
}
double
extrap_diff2 (double x, double h,
	     double (*f) (double x, void *params_ptr), void *params_ptr)
{
    return (4.*extrap_diff(x, h/2., f, params_ptr) -
                extrap_diff(x,h, f, params_ptr)) / 3.;
}