#ifndef TIMELINECSV_H
#define TIMELINECSV_H

#include <iostream> 
#include <fstream> 
#include <cstdio> 
#include "../Include/Utils/OriginPath.h" 
using namespace std;

namespace timeLineCSV
{

    // update functions
    void updateLoanNumber(int loanNb);
    void addNewMonth(int interestRate, int cusNb, int empNb, int loanNb);
    void updateInterestRate(int intRate);
    void updateAccountNumber(int cusNb);
    void updateEmployeeNumber(int empNb);

    // stringify helpers
    std::string stringifyInterestRateAsArray();
    std::string stringifyAccountsNumberAsArray();
    std::string stringifyEmployeesNumberAsArray();

    // last month getters
    std::string getlastMonthInterestRate();
    std::string getlastMonthAccountsNumber();
    std::string getlastMonthEmployeesNumber();
    std::string getlastMonthLoansNumber();

    // current month getters
    std::string getCurrentInterestRate();
    std::string getCurrentMonthAccountsNumber();
    std::string getCurrentMonthEmployeesNumber();

    // last month file
    std::string getLastMonth();
    void updateLastMonth(int Month);
}

#endif
