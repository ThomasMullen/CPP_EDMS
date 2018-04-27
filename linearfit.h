//
//  linearfit.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef linearfit_h
#define linearfit_h

#include "abstractexperimentfit.h"
/* ---------------------------
 Regression Statistic Structure
 ------------------------------
 Description:
 * The Regression Statistic struct stores all the constants used to find the gradient of a linear regression as a single variable.
 * The '+' operator has been overloaded such that the regressionStatistic accummulates Measumrements M that are added to it.
 -----------------------------*/

struct regressionStatistics{
    //Member variables:
    double xInvSqrErr, invSqrErr, yInvSqrErr, xInvErrSqrd, xyInvSqrErr, yInvErrSqrd;
    regressionStatistics();//Default Constructor
    regressionStatistics(Measurement&);//Parametised Constructor
    regressionStatistics & operator+(Measurement&);//Operator overload
};

/* ---------------------------
 LinearFit Experiment Class
 ------------------------------
 Description:
 * Derived class of AbstractExperiment. This is designed for experiments that are expected to fit a linear trend.
 
 Member Variables:
 * private RegVariable (regression variables) structure which contains:
 - Contains all the variable to construct a line of best fit to the data.
 - grad (gradient), gradErr (gradient error), intcpt (intercept), incptErr (intercept error).
 
 Functionality:
 * Private member function (only LinearFit can access):
 - Accumulate the regressionStatics of the LinearFit classes resultset.
 - Calculate the regression line variables for the resultset and return regVariables.
 - Calculate the Chi square of the regression line.
 * Public Memebr function:
 - produce a fit to the data and apply the private member functions and structs.
 -----------------------------*/
class LinearFit :
public AbstractExperimentFit{
    
private:
    //The Regression Variable struct stores constants that define the linear regression
    struct RegVariable{
        double grad; double gradErr;
        double intcpt; double intcptErr;
    };
    //Member Variables:
    double chiSqr;
    RegVariable regressionVariable;
    //Private Functions:
    regressionStatistics accumulateStats(); // Accumulates regression statistics
    RegVariable calculateRegressionLine(regressionStatistics& R)const;
    double calculateChiSqr(RegVariable& V, ResultsSet results)const;
    
public:
    //parametised constructor:
    LinearFit(string, ResultsSet);
    //Destructor
    ~LinearFit(){ resultsSet.clear(); }
    //Member Functions:
    void fitData();
    std::string getFittingParameters();
};
#endif /* linearfit_h */
