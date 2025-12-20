#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H

#include "../DataStructures/SinglyLinkedList.h"
#include "../Models/Employee.h"
#include "../Models/Customer.h"
#include "../Models/Account.h"
#include "../Models/Loan.h"
#include "../Models/Transaction.h"
#include "../Utils/MergeSort.h"
#include "../../CSV/AccountCSV.h"
#include "../../CSV/EmployeeCSV.h"
#include "../../CSV/TransactionCSV.h" 
#include "../../CSV/LoanCSV.h" 
#include "../../CSV/timeLineCSV.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace EmployeeController {

    // ---------------- Employee Management ----------------

    // Add a new employee | Adicionar um novo empregado
    inline void AddEmployee(
        Employee::Employee employees[], int& employeeCount,
        const string& name,
        const string& lastName,
        const string& address,
        const string& branch,
        const double& salary
    ) {
        if (employeeCount >= 50) { // MAX_EMPLOYEES
            return;
        }



        employees[employeeCount++] = Employee::Create(name, lastName, address, salary, branch);
        timeLineCSV::updateEmployeeNumber(employeeCount);
        EmployeeCSV::Write(employees, employeeCount); // Persist employees | Persistir empregados
    }

    // Edit employee information | Editar informações de um empregado
    inline void EditEmployee(
        Employee::Employee employees[], int employeeCount,
        const string& id,
        const double& salary,
        const string& branch,
        const string& status
    ) {

        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i].Id == id) {

                employees[i].Salary = salary;
                employees[i].BranchCode = branch;
                employees[i].Status = status;

                EmployeeCSV::Write(employees, employeeCount); // Update CSV | Atualizar CSV
                return;
            }
        }
        std::cout << "Employee not found!\n";
    }

    // Delete an employee | Deletar um empregado
    inline void DeleteEmployee(Employee::Employee employees[], int& employeeCount, const string& id) {

        int idx = 0;
        for (int i =0; i < employeeCount;i++)
        {
            if (employees[i].Id == id){
                idx = i;
                break;
            }
        }

        for (int j = idx; j < employeeCount-1;j++){
            employees[j] = employees[j+1];
        }
        employeeCount--;
        timeLineCSV::updateEmployeeNumber(employeeCount);
        EmployeeCSV::Write(employees, employeeCount); // Update CSV | Atualizar CSV
    }

    // View all employees sorted by last name | Mostrar todos os empregados ordenados pelo sobrenome
    inline void ViewEmployees(Employee::Employee employees[], int employeeCount) {
        if (employeeCount == 0) {
            std::cout << "No employees!\n";
            return;
        }

        Utils::MergeSort(employees, 0 ,employeeCount-1);
        for (int i = 0; i < employeeCount; ++i) {
            Employee::Display(employees[i]);
            std::cout << "-------------------\n";
        }
    }

    // ---------------- Account Management ----------------

    // Add a customer account | Adicionar uma conta para cliente
    inline void AddCustomerAccount(Customer::Customer customers[], int customerCount, Account::Account accounts[], int& accountCount,
                const string& Branch,
                const string& HolderName,
                const string& CustomerId,
                const string& Note,
                const string& Type
                ) {

                
        Customer::Customer* customer = nullptr;
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].Id == CustomerId) { 
                std::cerr << "kos om sisi";
                customer = &customers[i]; break; }
          
        }
        if (!customer) { return; }

        if (accountCount >= 200) { return; }


        accounts[accountCount] = Account::Create(HolderName, Type, Branch, "active", CustomerId , Note);
        Account::Account* accPtr = &accounts[accountCount];
        accountCount++;




        timeLineCSV::updateAccountNumber(accountCount);
        Customer::AddAccount(customer, *accPtr);
        AccountCSV::Write(accounts, accountCount); // Persist account | Persistir conta
    }

    // View all accounts | Mostrar todas as contas
    inline void ViewAccounts(Account::Account accounts[], int accountCount) {
        for (int i = 0; i < accountCount; ++i) {
            Account::Display(accounts[i]);
            std::cout << "-------------------\n";
        }
    }

    // Change account status | Alterar status da conta
    inline void ChangeAccountStatus(
        Account::Account accounts[], int accountCount,
        const string& accNumber,
        const string& status
    ) {

        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].AccountNumber == accNumber) {
                accounts[i].Status = status;
                AccountCSV::Write(accounts, accountCount); // Persist status change | Persistir alteração
                std::cerr << "Status updated successfully.\n";
                return;
            }
        }
    }

    // Delete all closed accounts | Deletar todas as contas fechadas
    inline void DeleteClosedAccounts(Account::Account accounts[], int& accountCount) {
        for (int i = 0; i < accountCount; ) {
            if (accounts[i].Status == "closed") {
                for (int j = i; j < accountCount - 1; ++j) accounts[j] = accounts[j + 1];
                accountCount--;
            } else {
                ++i;
            }
        }
        timeLineCSV::updateAccountNumber(accountCount);
        AccountCSV::Write(accounts, accountCount); // Update CSV | Atualizar CSV;
    }

    // ---------------- Loan Management ----------------

    // View customer loans | Visualizar loans de cliente
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

    // Change loan status | Alterar status de um loan
    inline void ChangeLoanStatus(Loan::Loan loans[], int loanCount, const string& loanId, const string& newState) {

        for (int i = 0; i < loanCount; ++i){
            if (loans[i].Id == loanId){
                loans[i].Status = newState;
            }
        }
        LoanCSV::Write(loans, loanCount);
    }

    // Delete completed loans | Deletar loans completos
    inline void DeleteLoan(Loan::Loan loans[], int& loanCount , const string& LoanId) {

        int Index = 0;
        for (int readIndex = 0; readIndex < loanCount; ++readIndex) {
            if (loans[readIndex].Id == LoanId) {
                Index = readIndex;
            }
        }
        
        for (int i = Index; i < loanCount - 1; ++i) {
            loans[i] = loans[i + 1];
        }
        loanCount--;
        LoanCSV::Write(loans, loanCount); // Update CSV | Atualizar CSV
    }

    // Manage loan requests | Gerenciar solicitações de loan
    inline void HandleSingleLoanRequest(
        const std::string& loanId,
        bool accept,

        Customer::Customer customers[], int customerCount,
        Account::Account accounts[], int& accountCount,
        Loan::Loan loans[], int& loanCount,
        Transaction::Transaction transactions[], int& transactionCount
    ) {
        // 1) Find the loan in the loans[] array
        int loanIndex = -1;
        for (int i = 0; i < loanCount; ++i) {
            if (loans[i].Id == loanId) {
                loanIndex = i;
                break;
            }
        }

        if (loanIndex == -1) {
            std::cout << "{\"status\":\"error\",\"message\":\"Loan request not found\"}" << std::endl;
            return;
        }

        Loan::Loan& request = loans[loanIndex];

        // 2) Handle rejection
        if (!accept) {
            // Remove loan from loans[] array
            for (int i = loanIndex; i < loanCount - 1; ++i) {
                loans[i] = loans[i + 1];
            }
            loanCount--;

            LoanCSV::Write(loans, loanCount); // Save updated loans
            std::cout << "{\"status\":\"ok\",\"message\":\"Loan refused and removed\"}" << std::endl;
            return;
        }

        // 3) Handle acceptance
        // Find the corresponding account
        Account::Account* acc = nullptr;
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].AccountNumber == request.AccountId) {
                acc = &accounts[i];
                break;
            }
        }

        if (!acc) {
            std::cout << "{\"status\":\"error\",\"message\":\"Account not found\"}" << std::endl;
            return;
        }

        // Apply loan to account balance
        acc->Balance += request.Amount;
        Account::AddLoan(acc, request);

        // Create transaction for loan deposit
        transactions[transactionCount++] = Transaction::Create(acc->AccountNumber, "loanDeposit", request.Amount);

        // Update loan status and type
        request.Status = "active";

        // Remove "request-" prefix from type if present
        request.type = request.type.substr(8);

        // Save all updates
        LoanCSV::Write(loans, loanCount);
        TransactionCSV::Write(transactions, transactionCount);
        AccountCSV::Write(accounts, accountCount);

        std::cout << "{\"status\":\"ok\",\"message\":\"Loan accepted\",\"loanId\":\""
                << loanId << "\"}" << std::endl;
}


    // Finalize daily transactions | Finalizar transações diárias
    inline void FinalizeTransactions() {

        Transaction::Transaction* transactions = nullptr;
        int transactionCount = 0;
        
        TransactionCSV::Write(transactions, transactionCount); // Update CSV | Atualizar CSV
    }

    // Find earliest and latest hired employees | Encontrar empregados mais antigos e mais recentes
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

    inline Employee::Employee* FindEmployee(Employee::Employee employees[], int employeeCount, const string& id){
        for(int i =0; i < employeeCount; ++i){
            if (employees[i].Id == id) return &employees[i];
        }
        return nullptr;
    }

}

#endif
