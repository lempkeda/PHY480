//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************// 

// include files
#include <iostream>	     // this has the cout, cin definitions
#include <iomanip>        // for setprecision
#define _USE_MATH_DEFINES  // for predefined pi value
#include <cmath>
#include <fstream>        // for outputting to file
using namespace std;     // if omitted, then need std::cout, std::cin 

//*********************************************************************//

const double pi = M_PI;   // define pi as a constant 

inline double square(double r) 
{ 
    return r*r; 
} 

double area_calc(double r){
	return pi* square(r);
}

int
main ()
{

  ofstream myfile;
  myfile.open ("area_new_output.txt");
  
  double radius;    // every variable is declared as int or double or ...
  cout << setprecision(12);
  cout << "Enter the radius of a circle: ";	// ask for radius
  cin >> radius;
  
  if (radius < 0){
  	cout << "Please do not enter a negative radius that doesnt make any sense why in the name of the lord would you do that? " << endl;
	return 0;	
  }

  double area = area_calc(radius);	// standard area formula

  cout << "radius = " << radius << ",  area = " << area <<endl;
  
  myfile << "Area = " << area;
  myfile.close();
  
  return 0;			// "0" for successful completion
}


//*********************************************************************//
