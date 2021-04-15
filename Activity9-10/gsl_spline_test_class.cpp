//  file: gsl_spline_test_class.cpp
// 
//  Test program for the gsl spline routines using the Spline class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from gsl_cubic_spline_test.cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation) 
//
//*****************************************************************
// include files
#include <iostream>    // cout and cin
#include <iomanip>     // manipulators like setprecision
#include <cmath>
#include <fstream>
#include <string>     // C++ strings                                 
using namespace std;    
#include "GslSpline.h"  // Header file for the GSL Spline class

inline double sqr (double z) {return z*z;}  // inline function for z^2

int
main (void)
{
  //const int NMAX = 300;   // maximum number of array points 
  //double xvalues[NMAX], yvalues[NMAX];

  ofstream out("spline.dat");

  // Test: interpolate y = sin(x^2) from xmin to xmax with npts points 
  //double xmin = 1.;
  //double xmax = 3.;
  int npts = 9;
  double xvalues[npts] = {0.,25.,50.,75.,100.,125.,150.,175.,200.};
  double yvalues[npts] = {9.34,17.9,41.5,83.5,51.5,21.5,10.8,6.29,4.09};
  /*
  double deltax = (xmax - xmin)/double(npts-1);
  for (int i = 0; i < npts; i++)
  {
    double x_temp = xmin + double(i) * deltax;   // grid of x points
    x_values[i] = x_temp;
    y_values[i] = sin (x_temp * x_temp);
  }
*/
  // Make the spline object
  //string type = "cubic";
  Spline my_cubic_spline (xvalues, yvalues, npts, "cubic");
  //Spline my_poly_spline (xvalues, yvalues, npts, "polynomial");
  Spline my_linear_spline (xvalues, yvalues, npts, "linear");
/*
  double x;
  cout << "Enter x: ";
  cin >> x;    // test point 

  // Evaluate the spline and derivatives
  double y = my_cubic_spline.y (x);
  double y_deriv = my_cubic_spline.yp (x);
  double y_deriv2 = my_cubic_spline.ypp (x);

  double x_sq = sqr(x);

  cout << "    x     y_exact   y_spline   y'_exact  y'_spline";
  cout << "  y''_exact  y''_spline" << endl;
  cout << fixed << setprecision(6) 
       << x << "  " << sin(x_sq) << "  " <<  y << "  "
       <<  2.*x*cos(x_sq) << "  " << y_deriv << "  "
       <<  -4.*x_sq* sin(x_sq) + 2.*cos(x_sq) << "  " <<  y_deriv2
       << endl;
*/
  for(double x = 0.; x <=200.; x+=5.){
    
    double y_cubic = my_cubic_spline.y (x); 
    //double y_poly = my_poly_spline.y (x); 
    double y_linear = my_linear_spline.y (x); 
    double actual = 63900./((sqr(x-78.0))+(sqr(55.0)/4.));

    out << fixed << setprecision(6) << x << "    " << actual << "    "
        << y_cubic << "    " /*<< y_poly << "    " */<< y_linear << "    "
        << endl;
  }
  out.close();
  return (0);      // successful completion 
}
