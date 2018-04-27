//
//  abstractexperimentfit.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "abstractexperimentfit.h"

/* -----------------------------
 Experiment Base Class Definitions
 -------------------------------*/

//#pragma warning(disable : 4996) //Allow Ctime to be used on VS compiler

//Declaring namespace variables used:
using std::cout; using std::left; using std::endl; using std::setw;

//Parametised constructor:
AbstractExperimentFit::AbstractExperimentFit(string _ExperimentName, ResultsSet _results) :
experimentName(_ExperimentName), resultsSet(_results){}

//Copy constructor:
AbstractExperimentFit::AbstractExperimentFit(const AbstractExperimentFit& Copy){
    for (size_t i{ 0 }; i < Copy.resultsSet.size(); i++) {
        resultsSet.push_back(Copy.resultsSet[i]);
    }
}

// Copy Assignment operator:
AbstractExperimentFit & AbstractExperimentFit::operator=(AbstractExperimentFit& Copy) {
    //object can't be assigned to itself;
    if (&Copy == this) return *this;
    resultsSet.clear();
    if (Copy.resultsSet.size() > 0) {
        for (size_t i = 0; i < Copy.resultsSet.size(); i++) {
            resultsSet[i] = Copy.resultsSet[i];
        }
    }
    return *this;
}

// Move constructor:
AbstractExperimentFit::AbstractExperimentFit(AbstractExperimentFit&& Move){
    resultsSet = Move.resultsSet;
    Move.resultsSet.clear();
}

// Move Assignment operator:
AbstractExperimentFit & AbstractExperimentFit::operator = (AbstractExperimentFit&& Move){
    resultsSet.clear();
    std::swap(resultsSet, Move.resultsSet);
    Move.resultsSet.clear();
    return *this;
}

//Append results to expisting result set:
void AbstractExperimentFit::appendResults(ResultsSet& newDataSet){
    resultsSet.insert(resultsSet.end(), newDataSet.begin(), newDataSet.end());
    std::sort(resultsSet.begin(), resultsSet.end());
    std::cout << "results appended and sorted." << std::endl;
}

//Ostream operator overload:
ostream & operator<<(ostream& os, const AbstractExperimentFit& AExp){
    // current date/time based on current system
    time_t now = time(0);
    char* dt = ctime(&now);
    os << "Experiment: " << AExp.experimentName << ". " << dt << endl;
    //Print Heading
    os << setw(13) << left << "" << setw(13) << left << "xValue" << setw(13) << left << "yValue" << setw(13) << left << "yError" << setw(13) << setw(13) << left << "Comb. Error" << endl;
    //Print measurements
    ResultsSet::iterator it;
    for (auto it = AExp.resultsSet.begin(); it != AExp.resultsSet.end(); ++it){
        os << *it;
    }
    return os;
}

