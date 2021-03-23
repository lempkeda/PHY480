
// integ.cpp
// Dave Lempke 3/21/2021
// PHY480 HW2
// Various integration routines
//


#include <iostream>
#include <cmath>
#include "integrate_routines.h"
#include <gsl/gsl_integration.h>

double simpsons_rule ( int num_pts, double x_min, double x_max, 
                      double (*integrand) (double x) )
{  
   double h = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero		 
   
   for (int n=2; n<num_pts; n+=2)                // loop for odd points  
   {
     double x = x_min + h * double(n-1);
     sum += (4./3.)*h * integrand(x);
   }
   for (int n=3; n<num_pts; n+=2)                // loop for even points  
   {
     double x = x_min + h * double(n-1);
     sum += (2./3.)*h * integrand(x);
   }   
   // add in the endpoint contributions   
   sum +=  (h/3.) * (integrand(x_min) + integrand(x_max));	
   
   return (sum);
}  


double milne ( int num_pts, double x_min, double x_max,
              double (*integrand) (double x) ){
   
   double h = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero		 
  
 
   // 14h/45   64h/45   24h/45   64h/45   14h/45     // 1 set of weights
   // 64h/45   24h/45   64h/45  28h/48               // sets of repeated weights except endpoints

   for (int n=2; n<num_pts; n+=2){
     double x = x_min + (h * double(n-1));          //every other weighted 54.35
     sum += (64./45.)*h * integrand(x);
   }

   for (int n=3; n<num_pts; n+=4){
     double x = x_min + (h * double(n-1));          // another weight
     sum += (24./45.)*h * integrand(x);
   }

   for (int n=5; n<num_pts; n+=4){
     double x = x_min + (h * double(n-1));           // last weight before repeat
     sum += (28./45.)*h * integrand(x);
   }

   sum +=  (14./45.) * h * (integrand(x_min) + integrand(x_max));	// add endpoints
   return sum;
}

double GSL_QAG_Gauss31 ( int num_pts, double x_min, double x_max,
              double (*integrand) (double x, void *) ){

  // GLS QAG gauss 31 point quadtrature
  // returns same answer no matter the num_pts used

  int max_intervals = num_pts - 1;
  
  gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (max_intervals);
  
  
  double lower_limit = x_min;	/* lower limit a */
  double upper_limit = x_max;	/* upper limit b */
  double abs_error = 1;	/* to avoid round-off problems */
  double rel_error = 1;	/* the result will usually be much better */
  double result;		/* the result from the integration */
  double error;			/* the estimated error from the integration */

  gsl_function My_function;
  My_function.function = *integrand;     // assign custom integrand to GSL function

  gsl_integration_qag (&My_function, lower_limit, upper_limit,  //GSL function call
		abs_error, rel_error, max_intervals,3, work_ptr, &result,
		&error);

  gsl_integration_workspace_free(work_ptr);    //do not think this is necesary
  return result;
}


