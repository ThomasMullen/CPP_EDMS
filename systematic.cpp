//
//  systematic.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "systematic.h"

/* -----------------------------
 Systematic Class Definitions
 -------------------------------*/

Systematic::Systematic(){}

Systematic::Systematic(double _xValue, double _yValue, double _mError, double _sError) :
Measurement(_xValue, _yValue, _mError), sError(_sError){
    cError = propagateErr();
}

//TODO check its not shallow copying
Systematic::Systematic(Systematic const& Copy){
    xValue = Copy.xValue;
    yValue = Copy.yValue;
    mError = Copy.mError;
    cError = Copy.cError;
    sError = Copy.sError;
}

Systematic::Systematic(Systematic&& Move){
    xValue = Move.xValue;
    yValue = Move.yValue;
    mError = Move.mError;
    sError = Move.sError;
    cError = Move.cError;
    Move.xValue = 0;
    Move.yValue = 0;
    Move.mError = 0;
    Move.cError = 0;
}

Systematic::~Systematic(){}

//Assignment Overloads:
Systematic& Systematic::operator =(Systematic& Copy){
    if (&Copy == this) return*this; //no self assignment
    //First delete this objects array
    sError = 0;
    sError = Copy.sError;
    Measurement::operator =(Copy);
    return *this; // Special pointer
}

//Move Overload
Systematic& Systematic::operator = (Systematic&& Move){
    std::swap(sError, Move.sError);
    Measurement::operator =(Move);
    return*this;
}

//less than Overload
bool Systematic::operator<(const Systematic& RHS)const{
    return std::tie(xValue, yValue, cError, mError) < std::tie(RHS.xValue, RHS.yValue, RHS.cError, RHS.mError);
}

//Measurement Output stream overload:
ostream & operator<<(ostream& os, const Systematic& M){
    using std::setw; using  std::left;
    os << "Measurement: " << setw(13) << left << M.getX() << setw(13) << left << M.getY() << setw(13) << left << M.getmErr() << setw(13) << left << M.getcErr() << std::endl;
    return os;
}

//function prototypes
measurement_ptr parse(const string & dataLine){
    using std::cout; using std::endl; using std::cerr;
    string dataPoint;
    std::stringstream dataValuesline(dataLine);
    //temporary container
    std::deque <double> dataValues;
//    //extract variables on line
    while (getline(dataValuesline, dataPoint, ',')){
        //convert and store variables
        try{
            dataValues.push_back(stod(dataPoint));
        }
        catch(...){
            throw ParseException(dataLine);
        }
    }
    //if size = 3 construct Measurement
    measurement_ptr spMeasurement;
    if (dataValues.size() == 3){
        cout << "Non-Systematic" <<endl;
        return spMeasurement = std::make_shared <Measurement>(dataValues[0], dataValues[1], dataValues[2]);
    }
    //if size = 4 construct Systematic
    else if (dataValues.size() == 4){
        cout << "Systematic" <<endl;
        return spMeasurement = std::make_shared <Systematic>(dataValues[0], dataValues[1], dataValues[2], dataValues[3]);
    }
    else{
        throw ParseException(dataLine);
    }
}
