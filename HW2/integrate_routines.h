//  file: integrate_routines.h
// 
//  Header file for integrate_routines.cpp

//  begin: function prototypes 
 

extern double simpsons_rule ( int num_pts, double x_min, double x_max, 
                       double (*integrand) (double x) );    // Simpson's rule 

extern double milne ( int num_pts, double x_min, double x_max, 
                       double (*integrand) (double x) );    // Milne integration 

extern double GSL_QAG_Gauss31 ( int num_pts, double x_min, double x_max, 
                       double (*integrand) (double x, void *) );    // GSL QAG 31 points 
//  end: function prototypes 
