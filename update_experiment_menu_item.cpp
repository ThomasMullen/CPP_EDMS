//
//  update_experiment_menu_item.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "menuitem.h"
/* -----------------------------
 Update Experiment Menu Item Class Definitions
 -------------------------------*/

//Action
void UpdateExperimentMenuItem::action(){
    std::cout << "Update experiment called." << std::endl;
    string existingExperimentName;
    try{
        std::cout << "Please enter an experiment in the list below that you would like to update.\n" <<std::endl;
        existingExperimentName = chooseExperiment();
        ResultsSet newResultSet = loadData();
        pApplication->updateExperiment(existingExperimentName, newResultSet);
    }
    catch(const FindException& fe){
        cerr<< fe.errorMessage <<endl;
    }

}
