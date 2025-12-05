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
    inline void TotalLoans(Customer::Customer customers[], int customerCount) {
        int total = 0;
        for (int i = 0; i < customerCount; i++) {
            auto accountNode = customers[i].Accounts.Head;
            while (accountNode) {
                total += accountNode->Data.Loans.Size;
                accountNode = accountNode->Next;
            }
        }
        std::cout << "Total Loans: " << total << "\n";
    }

    // Number of loans by type | Número de loans por tipo
    inline void LoansByType(Customer::Customer customers[], int customerCount) {
        int car = 0, home = 0, student = 0, business = 0, general = 0;
        for (int i = 0; i < customerCount; i++) {
            auto accountNode = customers[i].Accounts.Head;
            while (accountNode) {
                auto loanNode = accountNode->Data.Loans.Head;
                while (loanNode) {
                    std::string type = loanNode->Data.type;
                    if (type == "car") car++;
                    else if (type == "home") home++;
                    else if (type == "student") student++;
                    else if (type == "business") business++;
                    else if (type == "general") general++;
                    loanNode = loanNode->Next;
                }
                accountNode = accountNode->Next;
            }
        }
        std::cout << "Car Loans: " << car << "\n";
        std::cout << "Home Loans: " << home << "\n";
        std::cout << "Student Loans: " << student << "\n";
        std::cout << "Business Loans: " << business << "\n";
        std::cout << "General Loans: " << general << "\n";
    }

    // Number of loans by status | Número de loans por status
    inline void LoansByStatus(Customer::Customer customers[], int customerCount) {
        int active = 0, completed = 0, overdue = 0;
        for (int i = 0; i < customerCount; i++) {
            auto accountNode = customers[i].Accounts.Head;
            while (accountNode) {
                auto loanNode = accountNode->Data.Loans.Head;
                while (loanNode) {
                    std::string status = loanNode->Data.Status;
                    if (status == "active") active++;
                    else if (status == "completed") completed++;
                    else if (status == "overdue") overdue++;
                    loanNode = loanNode->Next;
                }
                accountNode = accountNode->Next;
            }
        }
        std::cout << "Active Loans: " << active << "\n";
        std::cout << "Completed Loans: " << completed << "\n";
        std::cout << "Overdue Loans: " << overdue << "\n";
    }

    // Active loans in date range | Loans ativos dentro de um intervalo de datas
    inline void ActiveLoansInDateRange(Customer::Customer customers[], int customerCount) {
        int day1, month1, year1, day2, month2, year2;
        std::cout << "Enter start date (dd mm yyyy): ";
        std::cin >> day1 >> month1 >> year1;
        std::cout << "Enter end date (dd mm yyyy): ";
        std::cin >> day2 >> month2 >> year2;

        Date::Date start{day1, month1, year1};
        Date::Date end{day2, month2, year2};

        int count = 0;
        for (int i = 0; i < customerCount; i++) {
            auto accountNode = customers[i].Accounts.Head;
            while (accountNode) {
                auto loanNode = accountNode->Data.Loans.Head;
                while (loanNode) {
                    Loan::Loan& L = loanNode->Data;
                    if (L.Status == "active") {
                        if ((L.StartDate.Year > start.Year || (L.StartDate.Year == start.Year && L.StartDate.Month > start.Month) ||
                            (L.StartDate.Year == start.Year && L.StartDate.Month == start.Month && L.StartDate.Day >= start.Day)) &&
                            (L.EndDate.Year < end.Year || (L.EndDate.Year == end.Year && L.EndDate.Month < end.Month) ||
                            (L.EndDate.Year == end.Year && L.EndDate.Month == end.Month && L.EndDate.Day <= end.Day))) {
                            count++;
                        }
                    }
                    loanNode = loanNode->Next;
                }
                accountNode = accountNode->Next;
            }
        }
        std::cout << "Active loans in the given date range: " << count << "\n";
    }

    // Customer with highest number of loans | Customer com mais loans
    inline void CustomerMostLoans(Customer::Customer customers[], int customerCount) {
        int maxLoans = -1;
        Customer::Customer* best = nullptr;
        for (int i = 0; i < customerCount; i++) {
            int loanCount = 0;
            auto accountNode = customers[i].Accounts.Head;
            while (accountNode) {
                loanCount += accountNode->Data.Loans.Size;
                accountNode = accountNode->Next;
            }
            if (loanCount > maxLoans) {
                maxLoans = loanCount;
                best = &customers[i];
            }
        }
        if (best) std::cout << "Customer with most loans: " << best->Name << " " << best->LastName << " (" << maxLoans << " loans)\n";
    }

    // Customer with highest balance | Customer com maior saldo
    inline void CustomerHighestBalance(Customer::Customer customers[], int customerCount) {
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
        if (richest) std::cout << "Customer with highest balance: " << richest->Name << " " << richest->LastName << " (" << maxBalance << " TND)\n";
    }

    // Customer with lowest balance | Customer com menor saldo
    inline void CustomerLowestBalance(Customer::Customer customers[], int customerCount) {
        double minBalance = 1e9;
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
        if (poorest) std::cout << "Customer with lowest balance: " << poorest->Name << " " << poorest->LastName << " (" << minBalance << " TND)\n";
    }

    // Total number of employees | Total de employees
    inline void TotalEmployees(Employee::Employee employees[], int employeeCount) {
        std::cout << "Total employees: " << employeeCount << "\n";
    }

    // Number of employees per branch | Número de employees por branch
    inline void EmployeesPerBranch(Employee::Employee employees[], int employeeCount) {
        struct BranchCount { std::string Branch; int Count; };
        BranchCount branches[50];
        int branchCount = 0;

        for (int i = 0; i < employeeCount; i++) {
            std::string branch = employees[i].BranchCode;
            bool found = false;
            for (int j = 0; j < branchCount; j++) {
                if (branches[j].Branch == branch) {
                    branches[j].Count++;
                    found = true;
                    break;
                }
            }
            if (!found && branchCount < 50) {
                branches[branchCount].Branch = branch;
                branches[branchCount].Count = 1;
                branchCount++;
            }
        }

        std::cout << "Employees per branch:\n";
        for (int i = 0; i < branchCount; i++) {
            std::cout << "Branch " << branches[i].Branch << ": " << branches[i].Count << "\n";
        }
    }

}

#endif
