//
//  weightedfit.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "weightedfit.h"

/* -----------------------------
 Constant Class Definitions
 -------------------------------*/

//Declaring namespace variables used:
using std::cout; using std::endl;

//paramterised constructor:
WeightedFit::WeightedFit(string _ExperimentName, ResultsSet _results) :
AbstractExperimentFit(_ExperimentName, _results){}

//Calculate the weighted mean/SD:
WeightedFit::WeightStatistics WeightedFit::calculateStatistics(){
    WeightStatistics total;
    //Lambda function to accumalte statistics:
    for_each(resultsSet.begin(), resultsSet.end(), [&total](Measurement R)->WeightedFit::WeightStatistics{
        total + R;
        return total;
    });
    return total;
}

//Construct the weighted statistic variables from the reuslts set measurements:
WeightedFit::WeightStatistics::WeightStatistics(Measurement& M){
    invSqrErr = 1 / pow(M.getcErr(), 2);
    yInvSqrErr = M.getY()*invSqrErr;
}

//Define Weighted constant data fit function:
void WeightedFit::fitData(){
    WeightStatistics variables = calculateStatistics();
    this->weightedMean = variables.yInvSqrErr / variables.invSqrErr; //Calculate the weighted mean
    this->weightedSD = sqrt(1 / pow(variables.invSqrErr, 2)); //Calculate the SD
    return;
}

std::string WeightedFit::getFittingParameters(){
    fitData();
    std::ostringstream os;
    os << "Weighted Values: " << this->weightedMean << " +/- " << this->weightedSD << endl;
    return os.str();
}

//Weighted Statistic accumulation overloads Definitions:
WeightedFit::WeightStatistics & WeightedFit::WeightStatistics::operator+(Measurement& M){
    WeightStatistics other(M);
    invSqrErr += other.invSqrErr;
    yInvSqrErr += other.yInvSqrErr;
    return *this;
}
