#include <iostream>    // note that .h is omitted
#include <iomanip>    // note that .h is omitted
#include <fstream>    // note that .h is omitted
#include <string>
#include <vector>
using namespace std;    // we need this when .h is omitted
#include <cmath>
#include "diffeq_routines.h"  // diffeq routine prototypes
#include <gsl/gsl_rng.h>	// GSL random number generators
#include <gsl/gsl_randist.h>	// GSL random distributions


// function prototypes
double rhs (double t, double y[], int i, vector<vector<parameters>> &vec);
vector<vector<parameters>> manual_setup();
vector<vector<parameters>> random_setup(const int & ,gsl_rng *);

int main(){

    const int N = 8;    // Number of species desired. 
    // any number of species is possible, but there is strange behavior past N= ~12 
    // with more species population feedback loops pop up 

    double y_rk4[N];    // vector of y functions 

    double tmin = 0;
    double tmax = 30;
    double h = 0.001;   //step size

    gsl_rng *rng_ptr;		                        //GSL RNG setup
    rng_ptr = gsl_rng_alloc (gsl_rng_taus);	

    ////////////////////////////////       ENTER SEED HERE       /////////////////////////////////////////////////
    unsigned long int seed = 412233;	     
    gsl_rng_set (rng_ptr, seed);

    ofstream out;          // declare the output file
    ofstream outgraph;     // output file for networkx graph
    out.open ("finalman.dat"); 
    outgraph.open("finalgraph.dat");

    
    vector<vector<parameters>> param_ary;
    //param_ary = manual_setup();              // Manual setup (make sure N=3)
    param_ary = random_setup(N ,rng_ptr);    // Random setup option
    
    for(int l = 0; l < N; l++){
        y_rk4[l] = gsl_ran_flat (rng_ptr, 2, 20);    // randomized starting populations
    }

    for (double t = tmin; t <= tmax; t += h)
    {
      // find y(t+h) by a 4th order Runge-Kutta step 
      runge4 (N, t, y_rk4, h, rhs, param_ary);
      out << t << "  ";
      for(int k = 0; k < N; k++){
          out << y_rk4[k] << "  ";
      }
      out << endl;
    }
  
    cout << " END OF SIMULATION UPDATED RELATIONSHIPS :" << endl;
    for(int i = 0; i < N; i++){                     
        if(param_ary[i][0].primary_comsumer_i){
            outgraph << 0 << " " << i+1 << endl;       // record arrows from primary food source to primary consumer 
        }
        cout << "Primary Consumer? = " << param_ary[i][0].primary_comsumer_i << endl;
        for(int j = 0; j < N; j++){
            cout << i+1 << j+1 << " = " << param_ary[i][j].relation << endl;
            if(param_ary[i][j].relation == "Predator"){ 
                outgraph << j+1 << " " << i+1 << endl;   // recording predator relationships in file for plotting nx graph
            }
        }
    }

    outgraph.close();
    out.close();   
    gsl_rng_free (rng_ptr);

    return 0;
}


//takes a vector representing a species interactions, and returns false if there is no valid food source
bool check_valid_species(vector<parameters> species){   
    bool valid = false;
    if(species[0].primary_comsumer_i){     // if they eat plants, theyre good
        valid = true;
    }
    for(int i = 0; i < static_cast<int>(species.size()); i++){
        if(species[i].relation == "Predator"){              // If they predate someone, theyre good.
            valid =true;                                    // This relationship is "Extinct" is the other party is extinct
        }
    }
    return valid;
}

double
rhs (double t, double y[], int i, vector<vector<parameters>> &vec)
{
    if(y[i] == 0)return 0;     // no change if the species is dead
    else if(y[i] <= .5){       // arbitrary cutoff point for extinction. This is necesary but value does not matter
        y[i] = 0;
        for(int k = 0; k < static_cast<int>(vec.size()); k++){  // change all relationships with species i to extinct
            vec[i][k].relation = "Extinct";
            vec[k][i].relation = "Extinct";
            
            if(!check_valid_species(vec[k])){                  // when any species goes extinct, check all species if they are valid
                for(int l = 0; l < static_cast<int>(vec.size()); l++){
                    vec[k][l].valid_i = false;
                }
            }
        }
        
        return 0.;
    }

    double result = 0;    // dPop/dt
    double sum_PC = 0;    // Sum of primary consumer pop

    if(t == 1000)cout << "AAA" << endl;
    for(int k = 0; k < static_cast<int>(vec.size()); k++){   // Sum together Primary Consumers for their common K
        if(vec[k][0].primary_comsumer_i){
            sum_PC += y[k];
        }
    }
    vector<parameters> species_vec = vec[i];     // vec for species in question
    result += species_vec[0].a_i * y[i];         // base growth rate
    
    if(species_vec[0].primary_comsumer_i){      // apply CC limit to PC
        result -= (species_vec[0].a_i * y[i] * sum_PC)/species_vec[0].K;    // Primary consumer term of diff eq
    }
    
    if(!species_vec[0].valid_i){      // quickly kill species if it is not valid
        result -= (species_vec[0].a_i * y[i] * y[i])/.25;
    }
    for(int j = 0; j < static_cast<int>(species_vec.size()); j++){ // loop through interactions
        parameters interact = species_vec[j];
        if(i != j){
            if(interact.relation == "Predator"){
                result -= (interact.a_i * y[i] * y[i])/(interact.k * y[j]);   //predator term of diff eq
            }
            else if(interact.relation == "Prey"){
                result -= (interact.b * y[i] * y[j])/(1 + (interact.b * y[i] * interact.t_h));   // prey term of diff eq
            }
        }
    }
    return result;
}

vector<vector<parameters>> manual_setup(){
    // this needs to be significantly change to change N
    //                  relation, PC, valid,grow_i, grow_j,PC_CC,Pred_CC, Pred rate(for prey), pred time
    parameters p11 = {"Neutral" ,false ,true, 2.0 , 1.0 , 100 , 2, .03, 1};
    parameters p12 = {"Predator",false ,true, 2.0 , 1.0 , 100 , 2, .03, 1};
    parameters p13 = {"Prey"    ,false ,true, 2.0 , 1.0 , 100 , 2, .003, 1};
    
    parameters p21 = {"Prey",true,true,6.0,1.0,750,2,.1,.1};
    parameters p22 = {"Neutral",true,true,6.0,1.0,750,2,.1,.1};
    parameters p23 = {"Neutral",true,true,6.0,1.0,750,2,.1,.1};

    parameters p31 = {"Predator",false,true,1.0,1.0,100,2,.1,.1};
    parameters p32 = {"Neutral",false,true,1.0,1.0,100,2,.1,.1};
    parameters p33 = {"Neutral",false,true,1.0,1.0,100,2,.1,.1};

    vector<vector<parameters>> param_ary2;
    vector<parameters> v1 = {p11,p12,p13};
    vector<parameters> v2 = {p21,p22,p23};
    vector<parameters> v3 = {p31,p32,p33};

    param_ary2.push_back(v1);
    param_ary2.push_back(v2);
    param_ary2.push_back(v3);
    return param_ary2;
}

vector<vector<parameters>> random_setup(const int & N,gsl_rng *rng_ptr){
    
    vector<vector<parameters>> param_ary_rand; 

    for(int l = 0; l < N; l++){
        vector<parameters> v_p;
        for(int m = 0; m < N; m++){     // making individual relationship
            parameters p;
            p.a_i = gsl_ran_flat (rng_ptr, 2, 3.0)*N ;    //growth rate
            p.a_j = 1.;                                   //this value is not used 
            p.K = 20 * N;                                 //The common primary consumer carrying capacity
            p.k = gsl_ran_flat (rng_ptr, 3, 4);           //hurts pred. 
            p.b = gsl_ran_flat (rng_ptr, 1, 2);           //hurts prey. 
            p.t_h = gsl_ran_flat (rng_ptr, .1, .2);       //helps prey. Time to be hunted
            
            double choose_side = gsl_ran_flat (rng_ptr, 0., 1.);  //choosing interaction
            if(choose_side < 0.7){
                p.relation = "Neutral";
            }
            else if(choose_side > 0.85){
                p.relation = "Predator";
            }
            else{
                p.relation = "Prey";
            }
            double PC = gsl_ran_flat (rng_ptr, 0, 1);   // Random chance for primary consumer
            if(PC < 0.2){
                p.primary_comsumer_i = true;
            }
            else{
                p.primary_comsumer_i = false;
            }
            if( l == m){
                p.relation = "Itself";
            }
            v_p.push_back(p);
        }
        param_ary_rand.push_back(v_p);
        //y_rk4[l] = gsl_ran_flat (rng_ptr, 2, 20);
    }

    // 2D array created now

    for(int i = 0; i < N; i++){    
        if(!check_valid_species(param_ary_rand[i])){   //checking species vector is see if it is valid
                for(int l = 0; l < static_cast<int>(param_ary_rand.size()); l++){
                    param_ary_rand[i][l].valid_i = false;
                }
        }
        
        cout << "Primary Consumer? = " << param_ary_rand[i][0].primary_comsumer_i << endl; // couting relationships
        // these couts are not really necesary with the networkx graph but i left them in
        
        for(int j = 0; j < N; j++){  // This loops makes sure the interactions are symmetric. Very important.
            if(param_ary_rand[i][j].relation == "Neutral"){
                param_ary_rand[j][i].relation = "Neutral";
            }
            else if(param_ary_rand[i][j].relation == "Predator"){
                param_ary_rand[j][i].relation = "Prey";
            }
            else if(param_ary_rand[i][j].relation == "Prey"){
                param_ary_rand[j][i].relation = "Predator";
            }

            cout << i+1 << j+1 << " = " << param_ary_rand[i][j].relation << endl;
        }
    }
    return param_ary_rand;
}