//
//  exit_menu_item.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 25/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
#include "menuitem.h"

/* -----------------------------
 Exit Menu Item Class Definitions
 -------------------------------*/

//Action:
void ExitMenuItem::action(){
    cout << "Are you sure you want to exit, any experiments that haven't been exported to file will be deleted? [Y/N]" << endl;
    char choice {' '};
    cin >> choice;
    if(choice == 'Y'){
        exit(1);
    }
    else{
        throw MenuException(choice);//send back to main menu
    }
}
