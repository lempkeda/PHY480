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
//
//		There is essentially no difference between summing up and summing down until you reach around N = 10,000-100,000.
//		From there the summing down method becomes more accurate as N increases obeying a power law relationship of around x^(3/2)
//		determined from the log-log plot. 

//		At large N, the summing up line starts to not change at all. While the summing down keeps increasing with N.
//		This is due to the fact that when you are summing up, large numbers are always being added first so when a large N is reached
//		there is no precision left in the memory for the summing to do anything. 
//		Summing down avoids this issue and is the better w

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
