//  file: summing.cpp
// 
//  Program to sum 1/n on the interval 1 to N:
//      a*x^2 + b*x + c = 0
//   Meant to compare summing up versus summing down
//
//  Programmer:  Dave Lempke lempkeda@msu.edu
//
//  Revision history:
//      02/14/2021  original version
//
//  Notes:

//************************************************************************ 

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
using namespace std;		// we need this when .h is omitted

//*********************************************************************//


int main(){
 
 
ofstream myfile;
myfile.open ("summing_output.dat");

cout << setprecision(8);

 for (int N = 10; N <= 100000000; N *= 2) 
 {
    float sum_up = 0, sum_down = 0, diff;
    
    for(int i=1.0; i<=N; i++){      ///    summing up here
    	sum_up += 1.0/i;
    }
    
    for(int j=N; j>=1; j--){      ///    summing up here
    	sum_down += 1.0/j;
    }
    
    diff = (fabs(sum_up - sum_down)) / (0.5*(sum_up + sum_down));     //Absolute value of the difference divied by their average. 
    
    
    
    myfile << "  " << fixed << setprecision(6)   
    <<  N  << "     " << diff << endl;

 }
 
 
return 0;
}
