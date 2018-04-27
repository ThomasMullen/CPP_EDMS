//
//  experimentCache.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef experimentCache_h
#define experimentCache_h

#include"weightedfit.h"
#include"linearfit.h"
#include "exceptions.h"
#include<iterator>
#include<map>

/* ---------------------------
 Experiment Cache Class
 ------------------------------
 Descriptions:
 * This Class is an experiement container where multiple users can temporarily store their experiments.
 
 Member variables:
 - Username -> The person name who is storing experiments
 - Dictionary -> This is a map of abstract experiment classes Key: Experiment name, Map: Experiment
 
 Functionality:
 - Can list the current temporary expeirments stored.
 - Find Experiments stored and return the pointer to that experiment
 - Export an experiment stored and the fit.
 - Print an experiment to screen.
 - Print existing user name.
 - Erase an existing experiment in the dicitonary.
 - Erase all experiments in the dictionary.
 -----------------------------*/

//Type Definitions:
typedef std::map<std::string, AbExpPtr> Dict;

class ExperimentCache{
private:
    const std::string username;
    Dict experimentContainer;
public:
    //Constructors & Destructors:
    ExperimentCache(){} //Default constructor
    ExperimentCache(const  std::string , Dict); //Parametised constructor
    ~ExperimentCache(){} //Destructor
    
    //Functions Definitions:
    string getUsername(){ return username; }
    AbExpPtr findExperiment(const string&)const;
    void storeExperiment(AbExpPtr);
    void eraseExperiment(const string&);
    void eraseAllExperiments();
    void printExperimentList()const;
};

#endif /* experimentCache_h */
