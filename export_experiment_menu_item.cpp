//
//  export_experiment_menu_item.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//
#include "menuitem.h"
/* -----------------------------
 Export Menu Item Class Definitions
 -------------------------------*/

//Action
void ExportMenuItem::action(){
    std::cout << "Export experiment called." << std::endl;
    string experimentName;
    try{
        experimentName = chooseExperiment();
    }
    catch(const FindException& fe){
        cerr<<fe.errorMessage<<endl;
    }
    std::cout << "Please enter an experiment you wish to export from the list above." << std::endl;
    AbExpPtr pExperiment = pApplication->returnExperiment(experimentName);
    cout << "Type 'F' to export to file or 'S' for screen" << endl;
    char option{' '};
    cin >> option;
    if( option == 'F' ){
        exportExperimentToFile(pExperiment);
    }
    else{
        cout << *pExperiment <<endl;
        cout << pExperiment->getFittingParameters() << endl;
    }
}

//Export Expeirment to File
void ExportMenuItem::exportExperimentToFile(const AbExpPtr& pExperiment){
    cout <<"Please enter the name you wish to save experiment as:" <<endl;
    string savedName;
    string userName = pApplication->getCacheName();
    cin >>savedName;
    savedName = savedName +"_"+ userName+ ".txt";
    string filePath {"/Users/Tom/Documents/University/Project/ExperimentData/"};
    std::ofstream exportFile(filePath+savedName);
    if (exportFile.is_open()){
        exportFile << *pExperiment;
        exportFile << pExperiment->getFittingParameters();
        exportFile.flush();
        exportFile.close();
    }
    else cerr << "Unable to open file"<<endl;
}
