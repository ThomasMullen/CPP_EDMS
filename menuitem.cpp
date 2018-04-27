//
//  menuitem.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#include "menuitem.h"

/* -----------------------------
 Menu Item Class Definitions
 -------------------------------*/
string MenuItem::chooseExperiment(){
    pApplication->getExperimentList(); //Print list of experiment
    string experimentName;
    cin >> experimentName;
    return experimentName;
}
