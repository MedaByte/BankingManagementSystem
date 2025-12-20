#ifndef STATISTICS_CONTROLLER_H
#define STATISTICS_CONTROLLER_H

#include "../Models/Customer.h"
#include "../Models/Loan.h"
#include "../Models/Account.h"
#include "../Models/Employee.h"
#include "../DataStructures/DoublyLinkedList.h"
#include "../DataStructures/SinglyLinkedList.h"
#include <iostream>
#include <string>


namespace StatisticsController {

    // Total number of loans | Total de loans
    inline int TotalLoans(Loan::Loan loan[], int loanCount) {
        return loanCount ;
    }

    // Number of loans by type | Número de loans por tipo
    inline int*LoansByType(Loan::Loan loan[], int loanCount) {
        if(!loanCount){
            int*arr = new int[5]{0,0,0,0,0};
            return arr;
        }
        string type ;
        int car = 0, home = 0, student = 0, business = 0, general = 0;
        for (int i = 0; i < loanCount; i++) {
            type = loan[i].type;
            if (std::toupper(type[0]) == 'C') car++;
            else if (std::toupper(type[0]) == 'H') home++;
            else if (std::toupper(type[0]) == 'S') student++;
            else if (std::toupper(type[0]) == 'B') business++;
            else if (std::toupper(type[0]) == 'G') general++;
        }
        
        int*res = new int[5]{business,car,home,student,general} ;// remember to free memory !!!
        return res ;
    }

    // Number of loans by status | Número de loans por status
    inline int*LoansByStatus(Loan::Loan loan[], int loanCount) {
        if(!loanCount){
            int*arr = new int[4]{0,0,0,0};
            return arr;
        }
        int active = 0, completed = 0, overdue = 0 , request = 0 ;
        string status ;
        for (int i = 0; i < loanCount; i++) {
            status = loan[i].Status;
            if (status == "active") active++;
            else if (status == "completed") completed++;
            else if (status == "overdue") overdue++;
            else if (status[0] == 'W') request++;
        }
        int*res = new int[4]{active,completed,overdue,request} ;// remember to free memory !!!
        return res ;
    }

    // Active loans in date range | Loans ativos dentro de um intervalo de datas
    inline int ActiveLoansInDateRange(Loan::Loan loan[], int loanCount, string startDate , string endDate) { // work on it
        if(!loanCount){
            return 0 ;
        }
    
        int day1, month1, year1, day2, month2, year2;
        int*arr1 = Utils::parseDate(startDate);
        int*arr2 = Utils::parseDate(endDate);


        day1 = arr1[0];
        month1 = arr1[1];
        year1 = arr1[2];

        day2 = arr2[0];
        month2 = arr2[1];
        year2 = arr2[2];


        delete[]arr1;
        delete[]arr2;

        Date::Date start{day1, month1, year1};
        Date::Date end{day2, month2, year2};

        int count = 0;
        for (int i = 0; i < loanCount; i++) {

            if (loan[i].Status == "active") {
                if ((loan[i].StartDate.Year > start.Year || (loan[i].StartDate.Year == start.Year && loan[i].StartDate.Month > start.Month) ||
                    (loan[i].StartDate.Year == start.Year && loan[i].StartDate.Month == start.Month && loan[i].StartDate.Day >= start.Day)) &&
                    (loan[i].EndDate.Year < end.Year || (loan[i].EndDate.Year == end.Year && loan[i].EndDate.Month < end.Month) ||
                    (loan[i].EndDate.Year == end.Year && loan[i].EndDate.Month == end.Month && loan[i].EndDate.Day <= end.Day))) {
                    count++;
                }
            }
                    
            
        }
        return count ;
    }

    inline int TotalNumberOfAccounts(Account::Account Acc[] , int AccountCount){
        return AccountCount ;
    }

    // Customer with highest number of loans | Customer com mais loans
    inline string*AccountMostLoans(Account::Account accarr[], int accCount) {
        if(!accCount){
            string*arr = new string[3]{"No Acc","0","No Acc"};
            return arr;
        }
        int maxLoans = -1;
        Account::Account* best = nullptr;
        string accId ;
        for (int i = 0; i < accCount; i++) {
            if(accarr[i].Loans.Size > maxLoans ){
                maxLoans = accarr[i].Loans.Size ; 
                best = &accarr[i];
            }
            
        }
        string*arr = new string[3]{best->AccountNumber,to_string(maxLoans),(best->HolderName)};
        return arr;
        
    }

    // Customer with highest balance | Customer com maior saldo
    inline string*CustomerHighestBalance(Customer::Customer customers[], int customerCount) {
        if(!customerCount){
            string*arr = new string[3]{"No Cus","0","No Cus"};
            return arr;
        }
        double maxBalance = -1;
        Customer::Customer* richest = nullptr;
        for (int i = 0; i < customerCount; i++) {
            auto accountNode = customers[i].Accounts.Head;
            double total = 0;
            while (accountNode) {
                total += accountNode->Data.Balance;
                accountNode = accountNode->Next;
            }
            if (total > maxBalance) {
                maxBalance = total;
                richest = &customers[i];
            }
        }
        string*arr = new string[3]{richest->Id,to_string(maxBalance),(richest->Name+" "+richest->LastName)};
        return arr;
    }

    // Customer with lowest balance | Customer com menor saldo
    inline string*CustomerLowestBalance(Customer::Customer customers[], int customerCount) {
        if(!customerCount){
            string*arr = new string[3]{"No Cus","0","No Cus"};
            return arr;
        }

        double minBalance = 1e12;
        Customer::Customer* poorest = nullptr;
        for (int i = 0; i < customerCount; i++) {
            auto accountNode = customers[i].Accounts.Head;
            double total = 0;
            while (accountNode) {
                total += accountNode->Data.Balance;
                accountNode = accountNode->Next;
            }
            if (total < minBalance) {
                minBalance = total;
                poorest = &customers[i];
            }
        }
        string*arr = new string[3]{poorest->Id,to_string(minBalance),(poorest->Name+" "+poorest->LastName)};
        return arr;
    }

    // Total number of employees | Total de employees
    inline int TotalEmployees(Employee::Employee employees[], int employeeCount) {
        return employeeCount;
    }

    // Number of employees per branch | Número de employees por branch
    inline int EmployeesPerBranch(Employee::Employee employees[], int employeeCount , int br) {
        if(!employeeCount){
            return 0 ; 
        }
        int acc = 0 ;
        for(int i = 0 ; i < employeeCount ; i++){
            if( stoi(employees[i].BranchCode) == br){acc++;}
        }
        return acc;
    }

    inline string*HighestSalaryEmployee(Employee::Employee emp[], int empC) {
        if(empC){
        int maxSal = -1;
        Employee::Employee*chosen = nullptr;
        string accId ;
        for (int i = 0; i < empC; i++) {
            if(emp[i].Salary > maxSal ){
                maxSal = emp[i].Salary ;
                chosen = &emp[i];
            }
            
        }
        string*arr = new string[3]{chosen->Id,to_string(chosen->Salary),chosen->Status};
        return arr;}
        else{
            string*arr = new string[3] {"No Emp","0","No Emp"};
        return arr;
        }
        
    }

    inline string*LowestSalaryEmployee(Employee::Employee emp[], int empC) {
        if(empC){
        int minSal = emp[0].Salary;
        Employee::Employee*chosen =  &emp[0];
        for (int i = 0; i < empC; i++) {
            if(emp[i].Salary < minSal ){
                minSal = emp[i].Salary ;
                chosen = &emp[i];
            }
            
        }
        string*arr = new string[3]{chosen->Id,to_string(chosen->Salary),chosen->Status};
        return arr;}
        else{
            string*arr = new string[3] {"No Emp","0","No Emp"};
            return arr;
        }
        
    }

}

#endif
