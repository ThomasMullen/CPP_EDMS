//
//  application.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//
#include "application.h"
#include "menuitem.h"

/* -----------------------------
 Application Class Definitions
 -------------------------------*/
void Application::getExperimentList(){
    experimentCache.printExperimentList();
    return;
}

//Create Experiment from fit type, name, result set
void Application::createExperiment(const string& experimentName,const char& fitType, ResultsSet& resultSet){
    //define abstractExperiment pointer
    AbExpPtr pExperiment;
    
    if (fitType =='L'){
        pExperiment = make_shared<LinearFit>(experimentName,resultSet);
    }
    
    else if (fitType =='W'){
        pExperiment = make_shared<WeightedFit>(experimentName,resultSet);
    }
    
    else{
        pExperiment = NULL;
    }
    //Providing its type is L/W fit and store experiment
    if(pExperiment){
        pExperiment->fitData();
        experimentCache.storeExperiment(pExperiment);
    }
    return;
}

//Return shared pointer pointing to an experiment
AbExpPtr Application::returnExperiment(const string& inputTitle){
    //find experiment
    AbExpPtr experiment = experimentCache.findExperiment(inputTitle);
    return experiment;
}

//Update an existing experiment with new data
void Application::updateExperiment(const string& existingExperimentName, ResultsSet& newDataSet){
    AbExpPtr existingExperiment = returnExperiment(existingExperimentName);
    existingExperiment->appendResults(newDataSet);
    existingExperiment->fitData();
}

//Delete a single experiment matching the inputted name
void Application::eraseSingleExperiment(const string& deleteNameExperiment){
    experimentCache.eraseExperiment(deleteNameExperiment);
}

string Application::getCacheName(){
    return experimentCache.getUsername();
}

void Application::eraseAll(){
    experimentCache.eraseAllExperiments();
}
