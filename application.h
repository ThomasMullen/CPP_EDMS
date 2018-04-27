//
//  application.hpp
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 22/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef application_h
#define application_h

#include "experimentCache.h"
/* ---------------------------
 Application Classes
 ------------------------------
 Description:
 *Contains a pure abstract Application base class: Interface to define the operations supported by the applications allow for future implementations to store data persistently in a relational database or in the cloud.
 * derived is application class: concrete implementation using in memory cache of Experimental data and calculated fits.

 
 Member Variables:
 - experimentCache-> This is so that the applications will have complete access to the experiment library and data point.
 
 Functionality:
 - Create new experiment -> it takes in the clean results set, expected fit type and experiment name; from this it can construct the data to a linear/weighted-fit experiment. This is then stored in the cache.
 - returnExperiment() -> This takes in a string name and iterates through the cache to checkif that experiment name exists. If so, it returns a base class pointer to the experiment.
 - updateExperiment() -> This takes in string and a clean data set and uses this to find the exisiting experiment and called the append results functions in the base class.
 - eraseExperiment(s)
    -> Single - takes in a name and iterates throught the cache removing the experiment that has the name.
    -> All - empties entire cache.
 - Return the the experiment cache users name.
 -----------------------------*/
using namespace std;

//namespace choices{
//    enum ExperimentTYPE{ linear = 1, constant = 2 };
//    map<string, ExperimentTYPE> trends;
//    void register_trendType(){
//        trends["Linear"] = linear;
//        trends["Constant"] = constant;
//    }
//}

/*-----------------------------
ApplicationI (Pure Virtual)
 -----------------------------*/
class ApplicationI
{
public:
    virtual void getExperimentList()=0;
    virtual void createExperiment(const string&, const char&, ResultsSet&)=0;
    virtual AbExpPtr returnExperiment(const string& inputTitle)=0;
    virtual void updateExperiment(const string&, ResultsSet&)=0;
    virtual void eraseSingleExperiment(const string&)=0;
    virtual void eraseAll()=0;
    virtual void exportExperiment(string& experimentName, unique_ptr <std::ostream>& out)=0;
    virtual string getCacheName()=0;
};

/*-----------------------------
 Application Class
 -----------------------------*/
class Application: public ApplicationI{
private:
    ExperimentCache experimentCache;
    
public:
    Application(const ExperimentCache& _experimentCache): experimentCache(_experimentCache) {}//Parametised constructor
    ~Application(){}
    //Define Functions
    void getExperimentList();
    void createExperiment(const string&, const char&, ResultsSet&);
    AbExpPtr returnExperiment(const string& inputTitle);
    void updateExperiment(const string&, ResultsSet&);
    void eraseSingleExperiment(const string&);
    void eraseAll();
    void exportExperiment(string& experimentName, unique_ptr <std::ostream>& out){
        return;
    }
    string getCacheName();
};
#endif /* application_h */
