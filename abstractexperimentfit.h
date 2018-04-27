//
//  abstractexperimentfit.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef abstractexperimentfit_h
#define abstractexperimentfit_h

#include"systematic.h"
#include<ctime>
#include<algorithm>

/* ---------------------------
 Abstract Base Experiment Class
 ------------------------------
 Description:
 * This is an abstract base class which stores experimental data and experiment name.
 * Member variable:
     - Results -> this stores Measurements in a vector.
     - Experiment name -> This is a so that experiments can be refered to and identified by the user.
 * Class Functionality:
     - Append results results to an existing results set.
     - Virtual fit data function, so that derived experiment types can plot fits to data.
     - return experiment name and resultset.
 -----------------------------*/
//Type definition:
typedef vector<Measurement> ResultsSet;

class AbstractExperimentFit{
    //Friend function:
    friend ostream & operator<<(ostream&, const AbstractExperimentFit&);
protected:
    //Member variable
    ResultsSet resultsSet;
    string experimentName;
    
public:
    //Constructors & Destructors:
    AbstractExperimentFit(string, ResultsSet); // Default
    AbstractExperimentFit(const AbstractExperimentFit&); // Copy constructor definition
    AbstractExperimentFit & operator = (AbstractExperimentFit&); // Copy Assignment operator
    AbstractExperimentFit(AbstractExperimentFit&&); // Move constructor definition
    AbstractExperimentFit & operator = (AbstractExperimentFit&&); // Move Assignment operator
    virtual ~AbstractExperimentFit(){} //Destructor
    
    //Memebr functions:
    virtual string getName()const{ return experimentName; } //Access experiment name
    virtual void appendResults(ResultsSet&); //Append results to existing result set
    
    //Pure Virtual fit data function:
    virtual void fitData() = 0;
    virtual std::string getFittingParameters() = 0;
};

//Type definition:
typedef std::shared_ptr<AbstractExperimentFit> AbExpPtr;

#endif /* abstractexperimentfit_h */
