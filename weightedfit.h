//
//  weightedfit.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef weightedfit_h
#define weightedfit_h
#include "abstractexperimentfit.h"

/* ---------------------------
 WeightedFit Experiment Class
 ------------------------------
 Description:
 * Derived class of AbstractExperiment. This is designed for experiments that are expected to find a constant value and thus calculate the weighted mean and standard deviation (SD).
 * Contains a nested statistics struct to hold all the accumulated measurement statistics.
 Member Variables:
 * private  weightstatistics (Weighted Statistics) structure which contains:
 - Stores all the constants used to find the the wieghted mean and SD as a single variable.
 - invSqrErr (inverse square of the combined error/measurement error), yInvSqrErr (measurement over the inverse square of the combined/measurement error).
 Functionality:
 * Private member function (only WeightedFit can access):
 - Accumulate the weightstatistics of the WeightedFit classes resultset.
 - The '+' operator has been overloaded such that the weightStatistics accummulates Measumrements M that are added to it.
 - Calculate the Weighted mean and SD for the resultset and return WeightStatistics.
 * Public Memebr function:
 - produce a fit to the data and apply the private member functions and structs.
 -----------------------------*/
class WeightedFit :
public AbstractExperimentFit{
public:
    WeightedFit(string, ResultsSet);
    ~WeightedFit(){ resultsSet.clear(); }
    //Member Functions:
    void fitData();
    std::string getFittingParameters();
private:
    //Member Variables
    double weightedMean;
    double weightedSD;
    
    //Private data struct contain all the statistics
    struct WeightStatistics{
        //Variables:
        double invSqrErr;
        double yInvSqrErr;
        //Default Constructor:
        WeightStatistics(){
            invSqrErr = 0; yInvSqrErr = 0;
        }
        //Parametised constructor:
        WeightStatistics(Measurement&);
        //overload operator:
        WeightStatistics & operator+(Measurement&);
    };
    //Calculate the Weighted Mean and SD
    WeightStatistics calculateStatistics();
};

#endif /* weightedfit_h */
