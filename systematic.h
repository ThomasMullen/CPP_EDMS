//
//  systematic.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef systematic_h
#define systematic_h

#include "measurement.h"
#include "exceptions.h"
#include<deque>
#include<limits>

/* ---------------------------
 Systematic Class
 ------------------------------
 Description:
 * Derived class of Measurement, used to store variables for each measurement taken. This additionally contains systematic error of the measurement.
 
 Member Variables:
 - Each measurement contains: xValue (dependent variable), yValue (independent variable), mError (measurement error), sError (Systematic error), cError (combined error uses quadrature in the constructor).
 
 Functionality:
 * Operator overload:
 - Asignment overload to copy and move measurements which is important when appending measurements to vectors.
 - Bool '<' operator used when sorting vectors of measurements.
 * Access variables to allow other classes and functions to access private memeber variables.
 * has a prototype function to parse input data to construct variable
 -----------------------------*/
class Systematic :
public Measurement
{
    friend ostream & operator<<(ostream&, const Systematic&);
    
private:
    double sError;
public:
    //Constructors & Destructors:
    Systematic();
    Systematic(double, double, double, double);
    Systematic(const Systematic&);
    Systematic(Systematic&&);
    ~Systematic();
    
    //Member fucntions:
    double getsErr()const{ return sError; }
    double propagateErr()const{ return sqrt(pow(sError, 2) + pow(mError, 2)); }
    
    //Assignment overload operators:
    Systematic& operator = (Systematic&);
    //Move Assignment Overload
    Systematic& operator = (Systematic&&);
    //less than Overload
    bool operator < (const Systematic&)const;
};

/* -----------------------------
 Parse Function
 --------------------------------
 Description:
 - Reads in a stringstream and dissociates the string via the getline delimiter ','.
 - Temporarily stores these strings into a template container.
 - Depending on the containers size will construct either a Measurement or Systematic object and return as a shared pointer.
 - If the arguement size isn't compatible it will return a null pointer and will be ignored in the later functions.
 -------------------------------*/

//function prototypes
measurement_ptr parse(const string &);

#endif /* systematic_h */
