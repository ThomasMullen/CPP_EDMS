//
//  create_experiment_menu_item.cpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
#include "menuitem.h"

/* -----------------------------
 Create Experiment Menu Item Class Definitions
 -------------------------------*/

//Get Experiment Name
string CreateExperimentMenuItem::getExperimentName(){
    std::cout << "Please enter a name for the experiment." <<std::endl;
    string experimentName;
    cin >> experimentName;
    return experimentName;
}

//Get Loading Method
char CreateExperimentMenuItem::getLoadingMethod(){
    char method {' '};//initiate char
    cout << "Please select a method to import data:\n[F] Add from file.\n[M] Add manually.\n[3] Escape." << endl;
    cin >> method;
    return method;
}

//Get File Name
std::string CreateExperimentMenuItem::getFileName(){
    const string filePath{ "/Users/Tom/Documents/University/Project/ExperimentData/" };//file directory
    string fileName;
    cout << "Please make sure the text files you want to open are in the following directory:" << filePath << ".\nPlease enter your file name:" << endl;
    cin >> fileName;
    fileName = filePath + fileName;
    cout << fileName << endl;
    return fileName;
}

//Get Fit Type
const char CreateExperimentMenuItem::getFitType(){
    cout << "Please enter the data trend expected from the experimental results Linear fit [L] or Weighted fit [W]: " << endl;
    char inputTrendtype {' '};
    cin >> inputTrendtype;
    return inputTrendtype;
}

//Load From File:TODO: open success -> change to a try catch exception
ResultsSet CreateExperimentMenuItem::loadFromFile(std::fstream& dataFile){
    //check open success
    if (dataFile.fail()){
        cerr << "File cannot open." << endl;
        exit(-1);
    }
    //initiate counters:
    int measurementCount{ 0 };
    int rogueDataCount{ 0 };
    ResultsSet CleanResultSet; //Instantiate Vector of clean measurements
    string measurementData; //Define string to extract line
    //read in line:
    while (getline(dataFile, measurementData)){
        try{
            measurementCount++;
            measurement_ptr spMeasurement;//shared pointer base class Measurement
            spMeasurement = parse(measurementData);//call parse function and test its valid
            if (spMeasurement){
                CleanResultSet.push_back(*spMeasurement);
            }
        }
        catch (const std::invalid_argument& ia){
            cerr << "Invalid argument: " << ia.what() << '\n';
            rogueDataCount++;
        }
        catch(const ParseException& pe){
            cerr << pe.errorMessage <<endl;
            rogueDataCount++;
        }
        catch (const exception& e){
            cerr << e.what() << endl;
        }
    }
    dataFile.clear();
    dataFile.close();
    cout << "Number of measurements read in: " << measurementCount << ". Number of readable measurements: " << CleanResultSet.size() << ". \nNumber of rogue measurements: " << rogueDataCount << endl;
    return CleanResultSet;
}

//Load Manually
ResultsSet CreateExperimentMenuItem::loadMannually(){
    cout << "Please enter a data point in the format: 'time, yValue, yError, systematicError'."<<endl;
    cout<<"When you have finished inputting data enter 'x' to escape." << endl;
    ResultsSet CleanResultSet;
    int rogueDataCount{ 0 };
    bool y{ true };
    while (y){
        string input;
        getline(cin,input);
//        cin.ignore(1000,'\n');
        cin.clear();
        try{
            //Check if user wants to exit loop
            if (input == "x"){
                break;
            }
            //Test input valid
            measurement_ptr spMeasurement;
            spMeasurement = parse(input);
            //if a measurement has been constructed:
            if (spMeasurement){
                CleanResultSet.push_back(*spMeasurement);
            }
        }
        catch(const ParseException& pe){
            cerr << pe.errorMessage <<endl;
            rogueDataCount++;
        }
        
        catch (const std::invalid_argument& ia){
            cerr << "Invalid argument: " << ia.what() << '\n';
            rogueDataCount++;
        }
//        catch (const std::exception& e){
//            cerr << e.what() << endl;
//        }
        //catch any other type of errors
        catch (...){
            cerr << "Unknown Error." << endl;
        }
    }
    cout << "Number rogue data points removed: " << rogueDataCount <<"."<<endl;
    cout<< "Number of readable measurements: " << CleanResultSet.size() << endl;
    return CleanResultSet;
}

//Load Data
ResultsSet CreateExperimentMenuItem::loadData(){
    ResultsSet empty;
    char method = getLoadingMethod(); //TODO: implement exception if invalid input
    if( method == 'M'){
        return loadMannually();
    }
    
    else if( method == 'F'){
        cout << "\nYou've selected add from file." << endl;
        cin.clear();
        string fileName = getFileName();
        std::fstream dataFile(fileName);
        return loadFromFile(dataFile);
    }
    //Else throw exception
    else
        throw MenuException(method);
}

//Action Function
void CreateExperimentMenuItem::action(){
    ResultsSet resultSet = loadData();
    pApplication->createExperiment(getExperimentName(),getFitType(), resultSet);
}


