//
//  erase_experiment_menu_item.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
#include "menuitem.h"

/* -----------------------------
 Erase Experiment Menu Item Class Definitions
 -------------------------------*/

//Return Erase option choice
char EraseExperimentMenuItem::getEraseOption(){
    std::cout << "Select:\n[1] To delete a specific experiment.\n[2] To delete entire cache.\n[back] To go back to main. menu." << std::endl;
    char option{' '};
    cin >> option;
    return option;
}

//Action:
void EraseExperimentMenuItem::action(){
    std::cout << "Erase experiment called." << std::endl;
    char option = getEraseOption();
    if (option == '1'){
        string experimentName = chooseExperiment();
        pApplication->eraseSingleExperiment(experimentName);
    }
    else if(option == '2'){
        pApplication->eraseAll();
    }
    else{
        throw MenuException(option);
    }
}
