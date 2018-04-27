//
//  experimentCache.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "experimentCache.h"
#include "menuitem.h"

/* -----------------------------
 Experiment Cache Class Definitions
 -------------------------------*/

//Declaring namespace variables used:
using std::string; using std::cout; using std::endl; using std::cin; using std::cerr;

//Parametised Constructor:
ExperimentCache::ExperimentCache(const  string _Username, Dict _experimentContainer) :
username(_Username), experimentContainer(_experimentContainer) {}

//Store Experiment function:
void ExperimentCache::storeExperiment(AbExpPtr pExp){
    //Add element to Map (Experiment Name, Experiment)
    experimentContainer[pExp->getName()] = pExp;
    cout << "Experiment Stored." << endl;
    return;
}

//Print Experiment List Function:
void ExperimentCache::printExperimentList()const{
    //Check Map not empty:
    if (experimentContainer.empty()){
        throw ListException();
        
    }
    else{
    //Print list on screen (Lambda function):
    cout << "list:\n" << endl;
    for_each(experimentContainer.begin(), experimentContainer.end(), [](std::pair<string, AbExpPtr> element){
        cout << element.first << endl;
    });
    }
    return;
}

//Erase Specific experiment:
void ExperimentCache::eraseExperiment(const string& deletedName){
    Dict::iterator it = experimentContainer.find(deletedName); //Define iterator to find experiment in map
    //If Experiment name not found:
    if (it != experimentContainer.end()){
        experimentContainer.erase(it);
        cout << "Experiment deleted." << endl;
    }
    else{
        throw FindException(deletedName);
    }
}

//Find experiment in Dictionary:
AbExpPtr ExperimentCache::findExperiment(const string& experimentName)const{
    auto it = experimentContainer.find(experimentName); //Define iterator to find experiment in map
    if (it == experimentContainer.end()){
        throw FindException(experimentName);
    }
    else{
        cout << "Experiment: " << it->first <<" selected."<< endl;
    }
    return it->second; //Return experiment
}

//Erase All Experiments:
void ExperimentCache::eraseAllExperiments(){
    experimentContainer.clear();
    cout << "All Experiments deleted." << endl;
}
