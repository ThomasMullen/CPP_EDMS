//
//  ui.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 23/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef ui_hpp
#define ui_hpp
#include "exceptions.h"
#include "application.h"
#include "menuitem.h"
/* ---------------------------
 User Interface Class
 ------------------------------
 Description:
 This class contains the programmes main function which allows the user to initiate their Cache, print the main menu and direct the main menu options to the application class.
 
 Member Variables:
 This class contains no member variables as its purely functional.
 
 Functionality:
 InitiateCache(): Is designed ask the current user for a username so the experiment library can be instantiated and all the experiments they export to file will contain the username in the saved name.
 PrintMenu(): Iterates throught the vector of MenuItems (derived main options in the main menu) and prints out their description.
 Operate overload (): This overload contains the bulk of the program and allows the program to run. It outlines the purpose of the program, as well as, provide the menu options in the. This is in a do while loop which can only be broken by selecting the ExitMenuItem.
 -----------------------------*/

class UI{
public:
    ExperimentCache initiateCache(); //gets user to instantiate Experiment library
    void printMenu(std::vector<shared_ptr<MenuItem>>& options); //Print all menu items
    void operator()(); //() overloaded to run program
};

#endif /* ui_hpp */
