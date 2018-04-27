//
//  menuitem.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//
#ifndef menuitem_h
#define menuitem_h
#include "application.h"
#include "exceptions.h"
#include <exception>

/* ---------------------------
Base Class: Menu Item
 -----------------------------
 Description:
 * This is an abstract base class, that contains the menu item options and provides the user interface. This and the derived classes contains most of the user iostream and returns key input options/string for the application to use and operate on.
 
 Member Variables:
 - menuTitle -> is the title of the the experiment this is hard defined in the constructor.
 - index -> This is a unique number each menu item has, it is defined the the UI class so each instance has a reference to select.
 - pApplication -> This is an abstract base class pointer to ApplicationI, it is used to polymorphically perform the action the menu item has been assigned.
 
 Functionality:
 - Pure virtual function action() which is the main function all menu items have.
 - description() method to print the menu's index and title.
 -----------------------------*/
typedef std::shared_ptr<ApplicationI> AppPtr;

class MenuItem{
protected:
    string chooseExperiment();
    std::string menuTitle;
    int index;
    AppPtr pApplication;
    
public:
    MenuItem(string _menuTitle, int _index, AppPtr _pApplication): menuTitle(_menuTitle), index(_index), pApplication(_pApplication) {}
    virtual void action()=0;
    virtual string description(){
        return "Choose: " + to_string(this->index) + " for " + this->menuTitle;
    }
    virtual ~MenuItem(){}
};

/* ---------------------------
 Create Experiment Menu Item
 -----------------------------
 * This is a base class which is used to create a new experiment. For it to construct a new experiment it requires the fitting type, name, and source of measurements
 Functionality:
 - Only public fucntion is action() the rest of the functions are protected as they are only useful to the actions or derived classes actions.
 - Method of loading data. It can read in data from file or manually returning a vector of Measruements/Systematic.
 - Private functions that return the name, fstream of file and fit type.
 -----------------------------*/
class CreateExperimentMenuItem: public MenuItem{
    
protected:
    string getExperimentName(); //user input experiment name
    const char getFitType(); //user input what fit type
    char getLoadingMethod(); //user selects what method resultset will be imported
    std::string getFileName(); //user inputs the file name
    ResultsSet loadFromFile(std::fstream& dataFile);
    ResultsSet loadMannually();
    ResultsSet loadData();
    
public:
    CreateExperimentMenuItem( int _index, AppPtr _pApplication): MenuItem("Create New Experiment", _index, _pApplication) {}
    //Parametised for derived constructors
    CreateExperimentMenuItem(string _menuTitle,  int _index, AppPtr _pApplication): MenuItem(_menuTitle, _index, _pApplication) {}
    virtual void action();
    virtual ~CreateExperimentMenuItem(){}
};

/* ---------------------------
 Update Menu Item Class
 -----------------------------
 Description:
 * Derived from the Create Experiment menu item as it contains all the functionality but the fittig type.
 -----------------------------*/
class UpdateExperimentMenuItem: public CreateExperimentMenuItem{
    
public:
    UpdateExperimentMenuItem(int _index, AppPtr _pApplication): CreateExperimentMenuItem( "Update experiment", _index, _pApplication) {}
    virtual void action();
    virtual ~UpdateExperimentMenuItem(){}
};

/* ---------------------------
 Export Menu Item Class
 -----------------------------
 Description:
 * Export menu allows the user to export experiments to file or to screen.
 Functionality:
 - Choose experiment to export, asks if user wants to print just on screen or to file.
 - If user selects other will automatically print to screen just in case it was a typo.
 - Export to file: The fileName will consist of the users inputted name and attached with that the ExperimentCache userName.
 -----------------------------*/
class ExportMenuItem: public MenuItem{
private:
    void exportExperimentToFile(const AbExpPtr&);
    
public:
    ExportMenuItem(int _index, AppPtr _pApplication): MenuItem( "Export experiment", _index, _pApplication) {}
    virtual void action();
    virtual ~ExportMenuItem(){}
};

/* ---------------------------
 Erase Menu Item
 -----------------------------
 Decription:
 * This menu allows the user to remove experiments that are stored in the cache. They have multiple options, they can removed a specific experiment or they can remove all.
 Functionality:
 - remove a single experiment, this takes a string of the desired experiment and will iterate through cache.
 - If the experiment is not found a a FindException is throuwn and the user is returned back to the main menu.
 -----------------------------*/
class EraseExperimentMenuItem: public MenuItem{
private:
    char getEraseOption();
public:
    EraseExperimentMenuItem(int _index, AppPtr _pApplication): MenuItem( "Erase experiment", _index, _pApplication) {}
    virtual void action();
    virtual ~EraseExperimentMenuItem(){}
};

/* ---------------------------
 Exit Menu Item
 -----------------------------
 Description:
 * This item contains as signle action which throws an exception to alert the user that if he exits the program, all unsaved data will be lost. Then asks the user to confirm choice.
 -----------------------------*/
class ExitMenuItem: public MenuItem{
public:
    ExitMenuItem(int _index, AppPtr _pApplication): MenuItem( "Exit Program", _index, _pApplication) {}
    virtual void action();
    virtual ~ExitMenuItem(){}
};

#endif /* menuitem_hpp */
