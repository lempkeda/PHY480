//  file: gsl_monte_carlo_test.cpp
//
//  Demo of Monte Carlo integration routines from GSL numerical library.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/19/05  original version, based on Monte_Carlo_test.cpp
//
//  Notes:  
//   * For more details, see the GNU Scientific Library Reference Manual
//   * Compile and link with:
//  g++ -Wall -o gsl_monte_carlo_test gsl_monte_carlo_test.cpp -lgsl -lgslcblas
//
//*********************************************************************//

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
//#include <math> 
using namespace std;

#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_vegas.h>


// Function prototypes
extern unsigned long int random_seed ();	// routine to generate a seed
double my_integrand (double *x, size_t dim, void *params);
void display_results (const char *title, double result, double error);

const double exact = 155./6.;

//*********************************************************************//

int
main ()
{
  // details of the integrand
  const int dimension = 10;   // dimension of integral
  
  // set upper and lower limits
  double xl[dimension] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};     // (all 0's)
  double xu[dimension] = { 1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};     // (all 1's)

  // set up the random number generator
  gsl_rng *rng_ptr;		// declare pointer to random number 
                                //   generator (rng) 
  rng_ptr = gsl_rng_alloc (gsl_rng_taus);	// allocate the rng 
  unsigned long int seed = random_seed ();  // generate a random seed
  gsl_rng_set (rng_ptr, seed);	// seed the rng 

  // set up the function for Monte Carlo routines
  gsl_monte_function my_gsl_function = { &my_integrand, dimension, NULL };

  size_t calls = 1000000;
  double result, error;		// result and error


  // first use plain, uniform sampling
  gsl_monte_plain_state *my_plain_state = gsl_monte_plain_alloc (dimension);
  gsl_monte_plain_integrate (&my_gsl_function, xl, xu, dimension, calls, 
     rng_ptr, my_plain_state, &result, &error);
  gsl_monte_plain_free (my_plain_state);

  display_results ("plain", result, error);


  // now use the "miser" routine
  gsl_monte_miser_state *my_miser_state = gsl_monte_miser_alloc (dimension);
  gsl_monte_miser_integrate (&my_gsl_function, xl, xu, dimension, calls, 
    rng_ptr, my_miser_state, &result, &error);
  gsl_monte_miser_free (my_miser_state);

  display_results ("miser", result, error);


  // finally, use the "vegas" routine
  gsl_monte_vegas_state *my_vegas_state = gsl_monte_vegas_alloc (dimension);

    // first do 10000 points as a warm-up
  gsl_monte_vegas_integrate (&my_gsl_function, xl, xu, dimension, 10000, 
    rng_ptr, my_vegas_state, &result, &error);
  display_results ("vegas warm-up", result, error);

    // then watch convergence 50000 at a time
  cout << "converging... " << endl;
  for (int i=0; i < 2; i++)
    {
      gsl_monte_vegas_integrate (&my_gsl_function, xl, xu, dimension, 
         calls / 2, rng_ptr, my_vegas_state, &result, &error);
      cout
	<< "result = " << setprecision (6) << result
	<< " sigma = " << setprecision (6) << error
	<< " chisq/dof = " << setprecision (1) << my_vegas_state->chisq 
        << endl;
    }
  gsl_monte_vegas_free (my_vegas_state);

  display_results ("vegas final", result, error);

  return 0;
}

//*********************************************************************//

double
my_integrand (double *x, size_t dim, void *)
{
  double sum = 0.;
  
  for (int i = 0; i < int(dim); i++)
    {
      sum += x[i]; 
    }
  
  return cos(sum)*(1/sin(2*sum))*exp(sum);
}

//*********************************************************************//

void
display_results (const char *title, double result, double error)
{
  cout.setf (ios::fixed, ios::floatfield);	// output in fixed format
  cout.precision (6);		// 6 digits past the decimal point

  cout << title << " ==================" << endl;
  cout << "result = " << setw (9) << result << endl;
  cout << "sigma  = " << setw (9) << error << endl;
  cout << "exact  = " << setw (9) << exact << endl;
  cout << "error  = " << setw (9) << result - exact
    << " = " << setprecision (1) << setw (2)
    << fabs (result - exact) / error << " sigma " << endl << endl;
}
