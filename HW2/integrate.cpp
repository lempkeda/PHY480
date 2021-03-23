// integrate.cpp
// Dave Lempke 3/21/2021
// lempkeda@msu.edu
//
// Runs integration routines found in integrate_routines.cpp
// Simpsons rule, milne integration, and GSL routine
//
// Cannot get GSL routine to work for different numbers of points
// it returns a more accurate answer than either simpson
// or milne no matter what however. Even if the workspace is limited
// much below 1000 iterations, it preforms better than milne and simpson
//
/////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "integrate_routines.h"	// prototypes for integration routines

double my_integrand (double x);
double my_gsl_integrand (double x, void *);

int main(){
    const int max_intervals = 30001;	// maximum number of intervals
    const double lower = 0.0;	// lower limit of integration
    const double upper = M_PI*4.;	// upper limit of integration

    double answer = 8.*M_PI;  // exact answer
    double result = 0.;   // variable for results

    // open the output file stream
    ofstream integ_out ("integrate.dat");	// save data in integ.dat
    integ_out << "#  N   Simpsons     Milne      GSL_QAG_31  " << endl;
    integ_out << "#-----------------------------------------" << endl;

    for (int i = 5; i <= max_intervals; i += 4 )
    // starting at i=5 points because milne require 4i + 1 points and
    // simpson requires 2i + 1 to be at full performance.
        {
            integ_out << setw(4) << i;

            result = simpsons_rule(i, lower, upper, &my_integrand);
            //cout << log (fabs (result - answer)/answer) << endl;
            integ_out << "  " << scientific << (fabs (result - answer)/answer);

            result = milne(i, lower, upper, &my_integrand);
            integ_out << "  " << scientific << (fabs (result - answer)/answer);

            result = GSL_QAG_Gauss31(i, lower, upper, &my_gsl_integrand);
            integ_out << "  " << scientific << (fabs (result - answer)/answer);

            integ_out << endl;
        }
  cout << "data stored in integrate.dat\n";
  integ_out.close ();

  return (0);

/////////// custom integrands ////////////
}
double my_integrand (double x)
{
  return (x*x*cos(x));
}
// GSL workspace expects this void ptr so it is simple to just define it this way
double my_gsl_integrand (double x, void *)
{
   return (my_integrand(x));
} 


