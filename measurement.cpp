//
//  measurement.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "measurement.h"

using namespace std; //TODO: go through and remove namespace

/* -----------------------------
 Measurement Class Definitions
 -------------------------------*/

//Define Constructors:
//Parametised
Measurement::Measurement(double _xValue, double _yValue, double _mError) :
xValue(_xValue), yValue(_yValue), mError(_mError), cError(_mError){
    //sError = 0;
}
//Copy constructor:
Measurement::Measurement(Measurement const& Copy){
    xValue = Copy.xValue;
    yValue = Copy.yValue;
    mError = Copy.mError;
    cError = Copy.cError;
}

Measurement::Measurement(Measurement&& Move){
    xValue = Move.xValue;
    yValue = Move.yValue;
    mError = Move.mError;
    cError = Move.cError;
    Move.xValue = 0;
    Move.yValue = 0;
    Move.mError = 0;
    Move.cError = 0;
}

//Assignment Overloads:
Measurement & Measurement::operator=(Measurement &Copy){
    if (&Copy == this) return*this; //no self assignment
    //First delete this objects array
    xValue = yValue = mError = cError = 0;
    xValue = Copy.xValue;
    yValue = Copy.yValue;
    mError = Copy.mError;
    cError = Copy.cError;
    return *this; // Special pointer
}

//Move Overload
Measurement & Measurement::operator=(Measurement&& Move){
    using std::swap;
    swap(xValue, Move.xValue);
    swap(yValue, Move.yValue);
    swap(mError, Move.mError);
    swap(cError, Move.cError);
    return*this;
}

//less than Overload
bool Measurement::operator<(const Measurement& RHS)const{
    //std::tie used to as a priority of order
    return std::tie(xValue, yValue, cError, mError) < std::tie(RHS.xValue, RHS.yValue, RHS.cError, RHS.mError);
}

//Measurement Output stream overload:
ostream & operator<<(ostream& os, const Measurement& M){
    using std::setw; using  std::left; //formatting purposes
    os << "Measurement: " << setw(13) << left << M.getX() << setw(13) << left << M.getY() << setw(13) << left << M.getmErr() << setw(13) << left << M.getcErr() << std::endl;
    return os;
}

//because memebr variables const can't input measurements
istream & operator>>(istream& is, Measurement& M){
    cout << "Please enter your data in the following way: 'x, y, measruement error, systematic error'." << endl;
    double dataValues[3];
    for (int i{ 0 }; i < 3; i++)
        is >> dataValues[i];
    Measurement* pMeasurement = new Measurement(dataValues[0], dataValues[1], dataValues[2]);
    measurement_ptr spMeasurement(pMeasurement);
    /*cout << *spMeasurement << endl;*/
    return is;
}
