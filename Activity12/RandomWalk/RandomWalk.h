//  file: RandomWalk.h
// 
//  Header file for RandomWalk class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      05/24/04  adapted random_walk.cpp to define a RandomWalk class
//      02/13/06  made get_x and get_y inline
//
#include <gsl/gsl_rng.h>	// GSL random number generators
#include <gsl/gsl_randist.h>	// GSL random distributions

class RandomWalk
{
public:
  RandomWalk (double x0, double y0);	// constructor: initialize the walk

  ~RandomWalk ();		// destructor

  // use the automatically generated copy constructor

  void step ();			// take a random step

  double get_x () { return x;};	// get the current x coordinate

  double get_y () {return y;};	// get the current y coordinate

private:
  int npts;			// number of random steps so far

  double x;			// current x value
  double y;			// current y value

  double lower_limit;		// lower limit of uniform range of step size
  double upper_limit;		// upper limit of uniform range of step size

  double delta_x;		// x-component of step 
  double delta_y;		// y-component of step 

  gsl_rng *rng_ptr;		// pointer to random number generator (rng) 

};
