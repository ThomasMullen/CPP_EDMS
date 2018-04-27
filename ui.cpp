//
//  ui.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 23/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//
#include "ui.h"
/* -----------------------------
 User Interface Class Definitions
 -------------------------------*/

ExperimentCache UI::initiateCache(){
    cout << "Please enter a username:" << endl;
    string name;
    Dict experimentDictionary; //instantiate map (library of experiments)
    cin >> name;
    ExperimentCache cache(name, experimentDictionary); //construct cache
    cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return cache;
}

//void print menu to screen
void UI::printMenu(std::vector<shared_ptr<MenuItem>>& options){
    //iterate through vector of base class MenuItem and get item to call description
    for(auto iterator = options.begin(); iterator != options.end(); ++iterator){
        cout << (*iterator)->description() << endl;
    }
}

/* ---------------------------
 Run Program
 -----------------------------*/

void UI::operator()(){
    cout<<"███████╗██╗████████╗    ██████╗  █████╗ ███████╗███████╗"<<endl;
    cout<<"██╔════╝██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██╔════╝"<<endl;
    cout<<"█████╗  ██║   ██║       ██████╔╝███████║███████╗█████╗"<<endl;
    cout<<"██╔══╝  ██║   ██║       ██╔══██╗██╔══██║╚════██║██╔══╝"<<endl;
    cout<<"██║     ██║   ██║       ██████╔╝██║  ██║███████║███████╗"<<endl;
    cout<<"╚═╝     ╚═╝   ╚═╝       ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n\n\n\n\n"<<endl;
    cout<<"Introduction:\n\n"<<endl;
    cout<<"This Programme is designed to read in measurements sets"<<endl;
    cout<<"and store them into specific experiment types. You will "<<endl;
    cout<<"be able to apply fits to your experiments and export"<<endl;
    cout<<"your clean data set to screen or file. You can erase "<<endl;
    cout<<"experiments saved to the cache or alternatively update" <<endl;
    cout<<"existing experiments with new datasets. When your" <<endl;
    cout<<"measurment set has been read in, the program will"<<endl;
    cout<<"automatically remove rogue data points, and sort your" <<endl;
    cout<<"measurements in order depending on you dependent variable."<<endl;
    cout<<"All experiments will have a datestamp when of when it was"<<endl;
    cout<<"last modifies, if you input an option not provided in the"<<endl;
    cout<<"menu, you will be directed back to the main menu page."<<endl<<endl;
    
    //Initiate Library cache
    ExperimentCache cache = initiateCache();
    
    //Declare a shared pointer to Applications and construct with initiated cache
    AppPtr pApplication = make_shared<Application>(cache);
    
    //instantiate a menu item constainer
    std::vector<shared_ptr<MenuItem>> options;
    
    //fill menu vector with menu items
    options.push_back(make_shared<CreateExperimentMenuItem>(0,pApplication) );
    options.push_back(make_shared<UpdateExperimentMenuItem>(1,pApplication) );
    options.push_back(make_shared<ExportMenuItem>(2,pApplication) );
    options.push_back(make_shared<EraseExperimentMenuItem>(3,pApplication) );
    options.push_back(make_shared<ExitMenuItem>(4,pApplication) );
    
    do{
        try{
            cout << "Choose option number below" << endl;
            printMenu(options);
            int optionIndex;
            cin >> optionIndex;
            //Access element in options
            std::shared_ptr<MenuItem> pMenuItem = options[optionIndex];
            pMenuItem->action();
        }
        catch(const MenuException& me){
            cerr << me.errorMessage << endl;
        }
        catch(const ListException& le){
            cerr << le.errorMessage << endl;
        }
        catch(const FindException& fe){
            cerr << fe.errorMessage << endl;
        }
    } while(true);
}

