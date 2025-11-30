#ifndef CUSTOMER_CONTROLLER_H
#define CUSTOMER_CONTROLLER_H

#include <iostream>
#include <string>
#include "../Models/Customer.h"
#include "../Models/Account.h"
#include "../Models/Loan.h"
#include "../Models/Transaction.h"

namespace CustomerController {

    // ---------------- Find a customer by ID ----------------
    inline Customer::Customer* FindCustomer(Customer::Customer customers[], int customerCount, const std::string& Id) {
        for(int i = 0; i < customerCount; i++) {
            if(customers[i].Id == Id)
                return &customers[i];
        }
        return nullptr;
    }

    // ---------------- Create Customer ----------------
    inline Customer::Customer& CreateCustomer(
        Customer::Customer customers[],
        int& customerCount,
        const std::string& name,
        const std::string& lastName,
        const std::string& address,
        const std::string& phone
    ) {
        if(customerCount >= 100) {
            std::cout << "Customer limit reached!\n";
            throw std::runtime_error("Overflow");
        }

        // Create customer
        Customer::Customer C = Customer::Create(name, lastName, address, phone);

        // Add to array
        customers[customerCount] = C;

        return customers[customerCount++];
    }

    // ---------------- Create Account for a Customer ----------------
    inline Account::Account& CreateAccount(
        Account::Account accounts[],
        int& accountCount,
        Customer::Customer* C,
        const std::string& type,
        const std::string& pin
    ) {
        if(accountCount >= 200) {
            std::cout << "Account limit reached!\n";
            throw std::runtime_error("Overflow");
        }

        // Create account (auto-generated ID)
        Account::Account A = Account::Create(
            C->Name + " " + C->LastName,
            type,
            pin,
            "active",
            C->Id
        );

        // Link to customer
        Customer::AddAccount(C, A);

        // Add to array
        accounts[accountCount] = A;

        return accounts[accountCount++];
    }

    // ---------------- View all accounts of a customer ----------------
    inline void ViewAccounts(Customer::Customer* C) {
        std::cout << "--- Accounts for " << C->Name << " " << C->LastName << " ---\n";
        auto node = C->Accounts.Head;
        while(node) {
            Account::Display(node->Data);
            std::cout << "-----------------------\n";
            node = node->Next;
        }
    }

    // ---------------- View all loans of a customer ----------------
    inline void ViewLoans(Customer::Customer* C) {
        std::cout << "--- Loans for " << C->Name << " " << C->LastName << " ---\n";
        auto accNode = C->Accounts.Head;
        while(accNode) {
            auto loanNode = accNode->Data.Loans.Head;
            while(loanNode) {
                Loan::Display(loanNode->Data);
                std::cout << "-----------------------\n";
                loanNode = loanNode->Next;
            }
            accNode = accNode->Next;
        }
    }

    // ---------------- Request a loan ----------------
    inline void RequestLoan(Customer::Customer* C, Loan::Loan loanRequests[], int& loanRequestCount) {
        if(loanRequestCount >= 50) {
            std::cout << "Loan request limit reached!\n";
            return;
        }

        std::string accNum;
        double amount, interestRate;
        int duration;

        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if(!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "Enter loan amount: ";
        std::cin >> amount;
        std::cout << "Enter interest rate (0.05 = 5%): ";
        std::cin >> interestRate;
        std::cout << "Enter duration (months): ";
        std::cin >> duration;

        Loan::Loan L = Loan::Create(account->AccountNumber, amount, interestRate, duration);
        loanRequests[loanRequestCount++] = L;

        std::cout << "Loan request submitted successfully!\n";
    }

    // ---------------- Deposit money ----------------
    inline void Deposit(Customer::Customer* C) {
        std::string accNum;
        double amount;

        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if(!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "Enter deposit amount: ";
        std::cin >> amount;

        Transaction::Transaction T = Transaction::Create(accNum, "deposit", amount);
        Account::AddTransaction(account, T);

        std::cout << "Deposit successful! New Balance: " << account->Balance << " TND\n";
    }

    // ---------------- Withdraw money ----------------
    inline void Withdraw(Customer::Customer* C) {
        std::string accNum;
        double amount;

        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if(!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "Enter withdrawal amount: ";
        std::cin >> amount;

        if(amount > account->Balance) {
            std::cout << "Insufficient balance!\n";
            return;
        }

        Transaction::Transaction T = Transaction::Create(accNum, "withdrawal", amount);
        Account::AddTransaction(account, T);

        std::cout << "Withdrawal successful! New Balance: " << account->Balance << " TND\n";
    }


    // ---------------- View daily transactions ----------------
    inline void ViewTransactions(Customer::Customer* C) {
        std::string accNum;
        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if(!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "--- Transactions ---\n";
        auto node = account->DailyTransactions.List.Head;
        while(node) {
            Transaction::Display(node->Data);
            std::cout << "-----------------\n";
            node = node->Next;
        }
    }

    // ---------------- Undo last transaction ----------------
    inline void UndoTransaction(Customer::Customer* C) {
        std::string accNum;
        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if(!account) {
            std::cout << "Account not found!\n";
            return;
        }

        if(Stack::IsEmpty(account->DailyTransactions)) {
            std::cout << "No transactions to undo!\n";
            return;
        }

        Account::UndoLastTransaction(account);
        std::cout << "Last transaction undone successfully.\n";
    }

}

#endif
