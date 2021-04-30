//  file: diffeq_routines.h
// 
//  Header file for diffeq_routines.cpp
//
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision History:
//    02/07/04 --- original version converted from C version, 
//                  based on rk4.cpp from "Computational
//                  Physics" and derivative_test.cpp
//    02/14/04 --- added 2nd order Runge-Kutta routine       
//
//  To do:
//
//************************************************************************
#include <vector>
using namespace std;
typedef struct      // define a type to hold parameters 
{
  string relation;    // eats feeds or neutral
  bool primary_comsumer_i;    
  bool valid_i;       // is false when no food sources
  double a_i;         // growth rate of organism i 
  double a_j;         // growth rate or organism j
  
  double K;           // primary comsumption carrying capacity
  
  double k;           // predation carrying capacity
  
  double b;           // predation rate (for prey)
  double t_h;         // predation handling time (for prey)
   
}
parameters;  
// function prototypes 
extern int euler ( const int N, double t, double y[], double h,
	    double (*f) (double t, double y[], int i, void *params_ptr), 
            void *params_ptr );
 
extern int runge4 ( const int N, double t, double y[], double h,
	    double (*f) (double t, double y[], int i, vector<vector<parameters>> &vec), 
            vector<vector<parameters>> &vec );
 
extern int runge2 ( const int N, double t, double y[], double h,
	    double (*f) (double t, double y[], int i, void *params_ptr), 
            void *params_ptr );
 
