//
//  main.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//
#include "ui.h"
#include "application.h"
#include "menuitem.h"
#include "experimentCache.h"
#include "abstractexperimentfit.h"
#include "linearfit.h"
#include "weightedfit.h"
#include "measurement.h"
#include "systematic.h"

/* ---------------------------
 User Notes:
 * To read in data file please change the string filePath in 'create_experiment_menu_item.cpp: getFileName()' to be the complete directory of the file you want to enter.
 * To export please change the string filePath in 'export_experiment_menuitem.cpp: exportExperimentToFile(const AbExpPtr&)'.
 * add an exception for bad file reading
 -----------------------------*/
/* -----------------------------
 Main
 -------------------------------*/
UI ui;

int main(int argc, const char * argv[]){
    ui();
    return 0;
}

