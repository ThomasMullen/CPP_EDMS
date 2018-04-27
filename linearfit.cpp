//
//  linearfit.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "linearfit.h"

/* -----------------------------
 Linear Class Definitions
 -------------------------------*/

//Declaring namespace variables used:
using std::cout; using std::endl; using std::showpos; using std::noshowpos;


//Regression Statistic struct Constructors:
regressionStatistics::regressionStatistics(){
    xInvSqrErr = 0; invSqrErr = 0; xInvErrSqrd = 0;
    yInvSqrErr = 0; xyInvSqrErr = 0; yInvErrSqrd = 0;
}

//Parametised Resgression statistic Constructor
regressionStatistics::regressionStatistics(Measurement& M){
    invSqrErr = 1 / pow(M.getcErr(), 2);
    xInvSqrErr = M.getX()*invSqrErr;
    yInvSqrErr = M.getY()*invSqrErr;
    xInvErrSqrd = pow(M.getX(), 2)*invSqrErr;
    xyInvSqrErr = M.getX()*M.getY()*invSqrErr;
    yInvErrSqrd = pow(M.getY(), 2)*invSqrErr;
}

//Regression Statistic accumulation overloads Definitions:
regressionStatistics & regressionStatistics::operator+(Measurement& M){
    regressionStatistics aReading(M);
    xInvSqrErr += aReading.xInvSqrErr;
    invSqrErr += aReading.invSqrErr;
    yInvSqrErr += aReading.yInvSqrErr;
    xInvErrSqrd += aReading.xInvErrSqrd;
    xyInvSqrErr += aReading.xyInvSqrErr;
    yInvErrSqrd += aReading.yInvErrSqrd;
    return *this;
}

//Linear Parametised Constructors:
LinearFit::LinearFit(string _ExperimentName, ResultsSet _results) :
AbstractExperimentFit(_ExperimentName, _results){}

//Statistic accumulation function:
regressionStatistics LinearFit::accumulateStats(){
    regressionStatistics total; //instantiate regression statistic
    //lambda function to accumulate measurements to regression statistic (use &total to change final outcome)
    for_each(resultsSet.begin(), resultsSet.end(), [&total](Measurement aMeasurement){
        total + aMeasurement;
    });
    return total;
}

//Calculate Regression Line using summed regression statistics:
LinearFit::RegVariable LinearFit::calculateRegressionLine(regressionStatistics& R)const{
    RegVariable variables;
    variables.grad = (R.xyInvSqrErr*R.invSqrErr - R.yInvSqrErr*R.xInvSqrErr) / (R.xInvErrSqrd*R.invSqrErr - pow(R.xInvSqrErr, 2));
    variables.intcpt = (R.xInvErrSqrd*R.yInvSqrErr - R.xyInvSqrErr*R.xInvSqrErr) / (R.xInvErrSqrd*R.invSqrErr - pow(R.xInvSqrErr, 2));
    variables.gradErr = sqrt(R.invSqrErr / (R.xInvErrSqrd*R.invSqrErr - pow(R.xInvSqrErr, 2)));
    variables.intcptErr = sqrt(R.xInvErrSqrd / (R.xInvErrSqrd*R.invSqrErr - pow(R.xInvSqrErr, 2)));
    return variables;
}

//Calculate Chi Square using regression variables:
double LinearFit::calculateChiSqr(RegVariable& V, ResultsSet results)const{
    double chiSqr{ 0 };
    for_each(results.begin(), results.end(), [&chiSqr, V](Measurement R){
        double delta{ 0 };
        delta = R.getY() - (V.grad * R.getX()) - V.intcpt;
        chiSqr += pow(delta / R.getcErr(), 2);
    });
    return chiSqr;
}

//Define linear data fit function: TODO:do for weighted mean
void LinearFit::fitData(){
    regressionStatistics Sum = accumulateStats();
    this->regressionVariable = calculateRegressionLine(Sum);
    this->chiSqr = calculateChiSqr(regressionVariable, resultsSet);
    return;
}

std::string LinearFit::getFittingParameters(){
    fitData();
    std::ostringstream os;
    os << "Line of best fit (y = mx + c):\n y = " <<"(" << this->regressionVariable.grad << " +/- " << this->regressionVariable.gradErr << ") X " << showpos <<" "<< this->regressionVariable.intcpt << " (+/- " << noshowpos << this->regressionVariable.intcptErr << " )" << endl;
    os << "\u03C7 ^2: " << this->chiSqr << endl;
    return os.str();
}
