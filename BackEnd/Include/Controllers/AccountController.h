#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H

#include <iostream>
#include "../Models/Account.h"
#include "../Models/Customer.h"
#include "../Models/Loan.h"
#include "../Models/Transaction.h"

namespace AccountController {

    // Find account by account number in an array
    inline Account::Account* FindAccount(Account::Account accounts[], int accountCount, const std::string& accountNumber) {
        for(int i = 0; i < accountCount; i++) {
            if(accounts[i].AccountNumber == accountNumber)
                return &accounts[i];
        }
        return nullptr;
    }

    // Display all accounts in an array
    inline void ViewAccounts(Account::Account accounts[], int accountCount) {
        std::cout << "--- Accounts List ---\n";
        for(int i = 0; i < accountCount; i++) {
            Account::Display(accounts[i]);
            std::cout << "----------------------\n";
        }
    }

    // Change account status
    inline void ChangeStatus(Account::Account* A, const std::string& newStatus) {
        Account::ChangeStatus(A, newStatus);
        std::cout << "Account " << A->AccountNumber << " status changed to " << newStatus << "\n";
    }

    // Delete closed accounts from array and return count of deleted
    inline void DeleteClosedAccounts(Account::Account accounts[], int& accountCount) {
        int shift = 0;
        for(int i = 0; i < accountCount; i++) {
            if(accounts[i].Status == "closed") {
                shift++;
            } else if(shift > 0) {
                accounts[i - shift] = accounts[i];
            }
        }
        accountCount -= shift;
        std::cout << shift << " closed accounts deleted.\n";
    }

    // Add account to a customer
    inline void AddCustomerAccount(Customer::Customer* C, Account::Account accounts[], int& accountCount) {
        if(accountCount >= 200) {
            std::cout << "Max accounts reached!\n";
            return;
        }

        std::string holderName = C->Name + " " + C->LastName;
        std::string accType, branchCode, status;

        std::cout << "Enter account type (Savings/Current): ";
        std::cin >> accType;
        std::cout << "Enter branch code: ";
        std::cin >> branchCode;
        std::cout << "Enter status (active/inactive/closed): ";
        std::cin >> status;

        Account::Account A = Account::Create(holderName, accType, branchCode, status, C->Id);
        accounts[accountCount++] = A;
        Customer::AddAccount(C, A);

        std::cout << "Account created successfully!\n";
    }
}

#endif
