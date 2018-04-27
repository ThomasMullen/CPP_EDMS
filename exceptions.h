//
//  exceptions.h
//  UIExperimentProject
//
//  Created by Thomas Soares Mullen on 27/04/2018.
//  Copyright © 2018 Thomas Soares Mullen. All rights reserved.
//

#ifndef exceptions_h
#define exceptions_h
#include <string>
#include <sstream>
/* -----------------------------
 Exception Class Definitions
 -------------------------------*/

/* -----------------------------
 Parse Exception:
 -------------------------------
 - Designed to removed rogue data lines: invalid arguements entered, non-convertable string
 - Throws cerr << errorMessage
 -------------------------------*/
class ParseException/*: public std::exception*/{
public:
    const std::string dataLine;
    const std::string errorMessage;
    ParseException(const std::string& _dataline):
    dataLine(_dataline), errorMessage("Cannot parse ( " + _dataline + " ) into Measurement or Systematic-Measurement.") {}
    virtual ~ParseException() throw(){}
};

/* -----------------------------
 Menu Exception:
 -------------------------------
 - Designed to throw exceptions when invalid menu inputs are invalid
 - Throws cerr << errorMessage
 - Exceptions are caught right at the top of the main menu
 -------------------------------*/
class MenuException{
public:
    char dataLine;
    std::string errorMessage;
    MenuException(char& _userValue):
    dataLine(_userValue) {
        std::stringstream ss;
        ss << "Entry '" << _userValue << "' called return.";
        errorMessage = ss.str();
    }
    virtual ~MenuException() throw(){}
};
/* -----------------------------
 List Exception:
 -------------------------------
 - Throw exceptions when the experiment list is empty
 - As the list is only printed if experiments are currently stored
 -------------------------------*/
class ListException{
public:
    char dataLine;
    std::string errorMessage;
    ListException():
    errorMessage("Sorry Experiment container is empty. Please Create an experiment."){}
    virtual ~ListException() throw(){}
};

/* -----------------------------
 Find Exception:
 -------------------------------
 - Throws exceptions if the name the user eetered doesn't match the experiment name stored in the cache.
 -------------------------------*/
class FindException{
public:
    const std::string experimentName;
    const std::string errorMessage;
    FindException(const std::string& _dataline):
    experimentName(_dataline), errorMessage("Cannot find '" + _dataline + "' in cache.") {}
    virtual ~FindException() throw(){}
};
#endif /* exceptions_h */
