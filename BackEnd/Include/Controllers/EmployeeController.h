#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H

#include "../DataStructures/SinglyLinkedList.h"
#include "../Models/Employee.h"
#include "../Models/Customer.h"
#include "../Models/Account.h"
#include "../Models/Loan.h"
#include "../Models/Transaction.h"
#include "../../CSV/AccountCSV.h"
#include "../../CSV/EmployeeCSV.h"
#include "../../CSV/TransactionCSV.h" 
#include "../../CSV/LoanCSV.h" 
#include <iostream>
#include <string>
#include <algorithm>

namespace EmployeeController {

    // ---------------- Employee Management ----------------
    inline void AddEmployee(Employee::Employee employees[], int& employeeCount) {
        if (employeeCount >= 50) { // MAX_EMPLOYEES
            std::cout << "Employee array full!\n";
            return;
        }

        std::string name, lastName, address, branch;
        double salary;

        std::cout << "Enter Name: "; std::cin >> name;
        std::cout << "Enter Last Name: "; std::cin >> lastName;
        std::cout << "Enter Address: "; std::cin >> address;
        std::cout << "Enter Salary: "; std::cin >> salary;
        std::cout << "Enter Branch Code: "; std::cin >> branch;

        employees[employeeCount++] = Employee::Create(name, lastName, address, salary, branch);

        EmployeeCSV::Write(employees, employeeCount);
        std::cout << "Employee added successfully.\n";
    }

    inline void EditEmployee(Employee::Employee employees[], int employeeCount) {
        std::string id;
        std::cout << "Enter Employee ID to edit: ";
        std::cin >> id;

        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i].Id == id) {
                std::string name, lastName, address, branch, status;
                double salary;

                std::cout << "Enter new Name: "; std::cin >> name;
                std::cout << "Enter new Last Name: "; std::cin >> lastName;
                std::cout << "Enter new Address: "; std::cin >> address;
                std::cout << "Enter new Salary: "; std::cin >> salary;
                std::cout << "Enter new Branch Code: "; std::cin >> branch;
                std::cout << "Enter new Status: "; std::cin >> status;

                employees[i].Name = name;
                employees[i].LastName = lastName;
                employees[i].Address = address;
                employees[i].Salary = salary;
                employees[i].BranchCode = branch;
                employees[i].Status = status;

                EmployeeCSV::Write(employees, employeeCount);
                std::cout << "Employee updated successfully.\n";
                return;
            }
        }
        std::cout << "Employee not found!\n";
    }

    inline void DeleteEmployee(Employee::Employee employees[], int& employeeCount) {
        std::string id;
        std::cout << "Enter Employee ID to delete: ";
        std::cin >> id;

        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i].Id == id) {
                for (int j = i; j < employeeCount - 1; ++j)
                    employees[j] = employees[j + 1];
                employeeCount--;

                EmployeeCSV::Write(employees, employeeCount);
                std::cout << "Employee deleted successfully.\n";
                return;
            }
        }
        std::cout << "Employee not found!\n";
    }

    inline void ViewEmployees(Employee::Employee employees[], int employeeCount) {
        if (employeeCount == 0) {
            std::cout << "No employees!\n";
            return;
        }

        std::sort(employees, employees + employeeCount, [](const Employee::Employee& a, const Employee::Employee& b) {
            return a.LastName < b.LastName;
        });

        for (int i = 0; i < employeeCount; ++i) {
            Employee::Display(employees[i]);
            std::cout << "-------------------\n";
        }
    }

    // ---------------- Account Management ----------------
    inline void AddCustomerAccount(Customer::Customer customers[], int customerCount, Account::Account accounts[], int& accountCount) {
        std::string customerID;
        std::cout << "Enter Customer ID: ";
        std::cin >> customerID;

        Customer::Customer* customer = nullptr;
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].Id == customerID) { customer = &customers[i]; break; }
        }
        if (!customer) { std::cout << "Customer not found!\n"; return; }

        if (accountCount >= 200) { std::cout << "Account array full!\n"; return; }

        std::string holderName, type, branch, status;
        double balance;
        std::cout << "Enter Account Holder Name: "; std::cin >> holderName;
        std::cout << "Enter Account Type: "; std::cin >> type;
        std::cout << "Enter Branch Code: "; std::cin >> branch;
        std::cout << "Enter Status: "; std::cin >> status;

        accounts[accountCount] = Account::Create(holderName, type, branch, status, customerID);
        Account::Account* accPtr = &accounts[accountCount];
        accountCount++;

        Customer::AddAccount(customer, *accPtr);
        std::cout << "Account added successfully.\n";

        // Write to CSV immediately
        AccountCSV::Write(accounts, accountCount);
    }

    inline void ViewAccounts(Account::Account accounts[], int accountCount) {
        for (int i = 0; i < accountCount; ++i) {
            Account::Display(accounts[i]);
            std::cout << "-------------------\n";
        }
    }

    inline void ChangeAccountStatus(Account::Account accounts[], int accountCount) {
        std::string accNumber, status;
        std::cout << "Enter Account Number: ";
        std::cin >> accNumber;
        std::cout << "Enter new Status: ";
        std::cin >> status;

        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].AccountNumber == accNumber) {
                Account::ChangeStatus(&accounts[i], status);
                std::cout << "Status updated successfully.\n";
                // Update CSV immediately
                AccountCSV::Write(accounts, accountCount);
                return;
            }
        }
        std::cout << "Account not found!\n";
    }

    inline void DeleteClosedAccounts(Account::Account accounts[], int& accountCount) {
        for (int i = 0; i < accountCount; ) {
            if (accounts[i].Status == "closed") {
                for (int j = i; j < accountCount - 1; ++j) accounts[j] = accounts[j + 1];
                accountCount--;
            } else {
                ++i;
            }
        }
        std::cout << "Closed accounts deleted successfully.\n";
        AccountCSV::Write(accounts, accountCount); // Update CSV
    }

    // ---------------- Loan Management ----------------
    inline void ViewCustomerLoans(Customer::Customer customers[], int customerCount) {
        std::string custID;
        std::cout << "Enter Customer ID: "; std::cin >> custID;

        Customer::Customer* customer = nullptr;
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].Id == custID) { customer = &customers[i]; break; }
        }
        if (!customer) { std::cout << "Customer not found!\n"; return; }

        for (auto node = customer->Accounts.Head; node; node = node->Next) {
            for (auto loanNode = node->Data.Loans.Head; loanNode; loanNode = loanNode->Next) {
                Loan::Display(loanNode->Data);
                std::cout << "-------------------\n";
            }
        }
    }

    inline void ChangeLoanStatus(Customer::Customer customers[], int customerCount,
                                Loan::Loan loans[], int loanCount) {
        std::string custID, loanID, status;
        std::cout << "Enter Customer ID: "; std::cin >> custID;
        std::cout << "Enter Loan ID: "; std::cin >> loanID;
        std::cout << "Enter new Status: "; std::cin >> status;

        bool updated = false;
        Customer::Customer* customer = nullptr;
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].Id == custID) { customer = &customers[i]; break; }
        }
        if (!customer) { std::cout << "Customer not found!\n"; return; }

            for (auto node = customer->Accounts.Head; node; node = node->Next) {
                Loan::Loan* loan = Account::FindLoan(&node->Data, loanID);
                
                for (int i=0; i<loanCount; ++i){
                    if (loans[i].Id == loanID){
                        loans[i].Status = status;
                        updated = true;
                        break;
                    }
                }
                if (loan) {
                    Loan::ChangeStatus(loan, status);
                    LoanCSV::Write(loans, loanCount);
                    std::cout << "Loan status updated successfully.\n";
                    return;
                }
        }
        if (!updated)
        {
            std::cout << "loan not found";
        }
    }

    inline void DeleteCompletedLoans(Customer::Customer customers[], int customerCount,
                                    Account::Account accounts[], int accountCount,
                                    Loan::Loan loans[], int& loanCount
                                    ) {

        Singly::List<Account::Account> tmp = Singly::Create<Account::Account>();
        for (int i = 0; i < customerCount; ++i) {
            for (auto node = customers[i].Accounts.Head; node; node = node->Next) {
                for (auto loanNode = node->Data.Loans.Head; loanNode; ) {
                    if (loanNode->Data.Status == "completed") {
                        auto* toDelete = loanNode;
                        loanNode = loanNode->Next;
                        Doubly::RemoveByNode(&node->Data.Loans, toDelete);
                    } else loanNode = loanNode->Next;
                }
            }
        }

        int writeIndex = 0;
        for (int readIndex = 0; readIndex < loanCount; ++readIndex) {

            if (loans[readIndex].Status != "completed") {
                loans[writeIndex++] = loans[readIndex];
            }
        }
        loanCount = writeIndex;

        LoanCSV::Write(loans, loanCount);
    }

    // ---------------- Loan Requests ----------------
    inline void ManageLoanRequests(Customer::Customer customers[], int customerCount,
                                    Loan::Loan loanRequests[], int& loanRequestCount,
                                    Loan::Loan loans[], int& loanCount,
                                    Transaction::Transaction transactions[], int& transactionCount,
                                    Account::Account accounts[], int& accountCount
                                ) {
        for (int i = 0; i < loanRequestCount; ) {
            Loan::Loan& request = loanRequests[i];
            std::string decision;
            std::cout << "Loan Request ID: " << request.Id << ", Account: " << request.AccountId << ", Amount: " << request.Amount << "\n";
            std::cout << "Accept (y/n)? ";
            std::cin >> decision;

            if (decision == "y" || decision == "Y") {
                for (int j = 0; j < customerCount; ++j) {
                    Customer::Customer& cust = customers[j];
                    Account::Account* acc = Customer::FindAccount(&cust, request.AccountId);
                    if (acc) {
                        Account::AddLoan(acc, request);
                        acc->Balance += request.Amount;
                        Transaction::Transaction T = Transaction::Create(acc->AccountNumber, "loanDeposit", request.Amount);
                        transactions[transactionCount++] = T;
                        loans[loanCount++] = request;
                        for (int an=0; an< accountCount; ++an){
                            if (accounts[an].CustomerId == customers[j].Id && accounts[an].AccountNumber == acc->AccountNumber){
                                accounts[an] = *acc;
                                break;
                            }
                        }
                        break;
                    }
                }
                for (int k = i; k < loanRequestCount - 1; ++k) loanRequests[k] = loanRequests[k + 1];
                loanRequestCount--;
            } else if (decision == "n" || decision == "N") {
                for (int k = i; k < loanRequestCount - 1; ++k) loanRequests[k] = loanRequests[k + 1];
                loanRequestCount--;
            } else i++;
        }
        TransactionCSV::Write(transactions, transactionCount);
        AccountCSV::Write(accounts, accountCount);
        LoanCSV::Write(loans, loanCount);
        std::cout << "Loan requests processed.\n";
    }

    // ---------------- Finalize Daily Transactions ----------------
    inline void FinalizeTransactions(Account::Account accounts[], int accountCount, Transaction::Transaction transactions[], int& transactionCount) {
        for (int i = 0; i < accountCount; ++i) {
            while (!Stack::IsEmpty(accounts[i].DailyTransactions)) {
                Stack::Clear(&accounts[i].DailyTransactions);
            }
        }

        transactions = {};
        transactionCount = 0;
        
        TransactionCSV::Write(transactions, transactionCount);
        std::cout << "Daily transactions finalized.\n";
    }

    inline void FindEarliestAndLatestEmployees(Employee::Employee employees[], int employeeCount) {
        if (employeeCount == 0) {
            std::cout << "No employees available.\n";
            return;
        }

        Employee::Employee* earliest = &employees[0];
        Employee::Employee* latest   = &employees[0];

        for (int i = 1; i < employeeCount; i++) {
            if (Date::CompareDates(employees[i].HireDate, earliest->HireDate) == -1)
                earliest = &employees[i];
            else if (Date::CompareDates(employees[i].HireDate, latest->HireDate) == 1)
                latest = &employees[i];
        }

        std::cout << "\n=== Earliest Hired Employee ===\n";
        Employee::Display(*earliest);

        std::cout << "\n=== Latest Hired Employee ===\n";
        Employee::Display(*latest);
    }

}

#endif
