//
//  measurement.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef measurement_h
#define measurement_h

#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include<cmath>
#include<tuple>
#include<set>
#include<memory>

//Declaring namespace variables used:
using std::vector; using std::ostream; using std::istream; using std::string;

/* ---------------------------
 Measurement Class
 ------------------------------
 Description:
 * Based class Measurement, used to store variables for each measurement taken. This only contains the error of the measurement.
 
 Member Variables:
 - Each measurement contains: xValue (dependent variable), yValue (independent variable), mError (measurement error), cError (combined error in this case measurement error).
 
 Functionality:
 * Operator overload:
 - Asignment overload to copy and move measurements which is important when appending measurements to vectors.
 - Bool '<' operator used when sorting vectors of measurements.
 * Access variables to allow other classes and functions to access private memeber variables.
 
 -----------------------------*/
class Measurement{
    ////Friends:
    friend ostream & operator<<(ostream&, const Measurement&);
    friend istream & operator>>(istream&, Measurement&);
    
protected:
    double xValue;
    double yValue;
    double mError;
    //double sError;
    double cError;
public:
    //Constructors and Destructors:
    Measurement(){}
    Measurement(double, double, double);
    Measurement(Measurement const&);
    Measurement(Measurement&&);
    virtual ~Measurement(){}
    
    //Access functions:
    virtual double getX()const{ return xValue; }
    virtual double getY()const{ return yValue; }
    virtual double getmErr()const{ return mError; }
    virtual double getcErr()const{ return cError; }
    
    //Operator Overloads:
    //Copy Assignment Overload
    Measurement & operator = (Measurement&);
    //Move Assignment Overload
    Measurement & operator = (Measurement&&);
    //less than Overload
    bool operator < (const Measurement&)const;
    
};

// Type definition:
typedef std::shared_ptr<Measurement> measurement_ptr;

#endif /* measurement_h */
