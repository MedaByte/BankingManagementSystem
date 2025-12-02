#ifndef CUSTOMER_CONTROLLER_H
#define CUSTOMER_CONTROLLER_H

#include <iostream>
#include <string>
#include "../Models/Customer.h"
#include "../Models/Account.h"
#include "../Models/Loan.h"
#include "../Models/Transaction.h"
#include "../DataStructures/Stack.h"
#include "../../CSV/CustomerCSV.h"
#include "../../CSV/AccountCSV.h" 
#include "../../CSV/TransactionCSV.h" 

namespace CustomerController {

    // ---------------- Find a customer by ID ----------------
    inline Customer::Customer* FindCustomer(Customer::Customer customers[], int customerCount, const std::string& Id) {
        for (int i = 0; i < customerCount; ++i)
            if (customers[i].Id == Id) return &customers[i];
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
        if (customerCount >= 100) {
            std::cout << "Customer limit reached!\n";
            throw std::runtime_error("Overflow");
        }

        Customer::Customer C = Customer::Create(name, lastName, address, phone);
        customers[customerCount] = C;

        // Write full array to CSV
        CustomerCSV::Write(customers, customerCount + 1);

        return customers[customerCount++];
    }

    // ---------------- Create Account for a Customer ----------------
    inline Account::Account& CreateAccount(
        Account::Account accounts[],
        int& accountCount,
        Customer::Customer* C,
        const std::string& type,
        const std::string& pin,
        Customer::Customer customers[],
        int customerCount
    ) {
        if (accountCount >= 200) {
            std::cout << "Account limit reached!\n";
            throw std::runtime_error("Overflow");
        }

        Account::Account A = Account::Create(
            C->Name + " " + C->LastName,
            type,
            pin,
            "active",
            C->Id
        );

        Customer::AddAccount(C, A);
        accounts[accountCount] = A;

        // Write full accounts array to CSV
        AccountCSV::Write(accounts, accountCount + 1);
        // Also write customers to CSV to persist the updated accounts links
        CustomerCSV::Write(customers, customerCount);

        return accounts[accountCount++];
    }

    // ---------------- View all accounts of a customer ----------------
    inline void ViewAccounts(Customer::Customer* C) {
        std::cout << "--- Accounts for " << C->Name << " " << C->LastName << " ---\n";
        auto node = C->Accounts.Head;
        while (node) {
            Account::Display(node->Data);
            std::cout << "-----------------------\n";
            node = node->Next;
        }
    }

    // ---------------- View all loans of a customer ----------------
    inline void ViewLoans(Customer::Customer* C) {
        std::cout << "--- Loans for " << C->Name << " " << C->LastName << " ---\n";
        auto accNode = C->Accounts.Head;
        while (accNode) {
            auto loanNode = accNode->Data.Loans.Head;
            while (loanNode) {
                Loan::Display(loanNode->Data);
                std::cout << "-----------------------\n";
                loanNode = loanNode->Next;
            }
            accNode = accNode->Next;
        }
    }

    // ---------------- Request a loan ----------------
    inline void RequestLoan(Customer::Customer* C, Loan::Loan loanRequests[], int& loanRequestCount) {
        if (loanRequestCount >= 50) {
            std::cout << "Loan request limit reached!\n";
            return;
        }

        std::string accNum;
        double amount, interestRate;
        int duration;

        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if (!account) {
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
    inline void Deposit(Customer::Customer* C,
                        Account::Account accounts[], 
                        int accountCount,
                        Transaction::Transaction transactions[],
                        int& transactionCount){
        
        std::string accNum;
        double amount;

        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if (!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "Enter deposit amount: ";
        std::cin >> amount;

        Transaction::Transaction T = Transaction::Create(accNum, "deposit", amount);
        transactions[transactionCount++] = T;
        Account::AddTransaction(account, T);
        

        for (int i=0; i<accountCount; ++i){
            if (accounts[i].CustomerId == account->CustomerId && accounts[i].AccountNumber == accNum){
                accounts[i] = *account;
                Stack::Push(&accounts[i].DailyTransactions, T);

            }
        }


        TransactionCSV::Write(transactions, transactionCount);

        AccountCSV::Write(accounts, accountCount);
        std::cout << "Deposit successful! New Balance: " << account->Balance << " TND\n";
    }

    // ---------------- Withdraw money ----------------
    inline void Withdraw(Customer::Customer* C,
                        Account::Account accounts[], 
                        int accountCount,
                        Transaction::Transaction transactions[],
                        int& transactionCount) {
        
        std::string accNum;
        double amount;

        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if (!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "Enter withdrawal amount: ";
        std::cin >> amount;

        if (amount > account->Balance) {
            std::cout << "Insufficient balance!\n";
            return;
        }

        // Update balance
        account->Balance -= amount;

        // Create transaction
        Transaction::Transaction T = Transaction::Create(accNum, "withdrawal", amount);
        transactions[transactionCount++] = T;

        // Add transaction to customer's account
        Stack::Push(&account->DailyTransactions, T);

        // Update global accounts array
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].AccountNumber == accNum) {
                accounts[i] = *account; // copy updated balance and stack
                break;
            }
    
        }

        // Persist changes
        TransactionCSV::Write(transactions, transactionCount);
        AccountCSV::Write(accounts, accountCount);

        std::cout << "Withdrawal successful! New Balance: " << account->Balance << " TND\n";
}


    // ---------------- View daily transactions ----------------
    inline void ViewTransactions(Customer::Customer* C) {
        std::string accNum;
        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account* account = Customer::FindAccount(C, accNum);
        if (!account) {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "--- Transactions ---\n";
        auto node = account->DailyTransactions.List.Head;
        while (node) {
            Transaction::Display(node->Data);
            std::cout << "-----------------\n";
            node = node->Next;
        }
    }

    // ---------------- Undo last transaction ----------------
    inline void UndoTransaction(Customer::Customer* C,
                                Account::Account accounts[], 
                                int accountCount,
                                Transaction::Transaction transactions[],
                                int& transactionCount) {

        std::string accNum;
        std::cout << "Enter Account Number: ";
        std::cin >> accNum;

        Account::Account* account = Customer::FindAccount(C, accNum);
        if (!account) {
            std::cout << "Account not found!\n";
            return;
        }

        if (Stack::IsEmpty(account->DailyTransactions)) {
            std::cout << "No transactions to undo!\n";
            return;
        }

        // Pop last transaction from customer's account
        Transaction::Transaction lastTx = Stack::Top(account->DailyTransactions);
        Stack::Pop(&account->DailyTransactions);

        // Reverse its effect on balance
        if (lastTx.Type == "deposit") {
            account->Balance -= lastTx.Amount;
        } else if (lastTx.Type == "withdrawal") {
            account->Balance += lastTx.Amount;
        } else {
            std::cout << "Unknown transaction type!\n";
            return;
        }

        // Update global accounts array
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].AccountNumber == accNum) {
                accounts[i] = *account; // copy updated balance and stack
                break;
            }
        }

        // Remove last transaction from global transactions array
        bool removed = false;
        for (int i = transactionCount - 1; i >= 0; --i) {
            if (transactions[i].TransactionId == lastTx.TransactionId) {
                for (int j = i; j < transactionCount - 1; ++j) {
                    transactions[j] = transactions[j + 1];
                }
                --transactionCount;
                removed = true;
                break;
            }
        }

        if (!removed) {
            std::cout << "Warning: transaction not found in global array!\n";
        }

        // Persist changes
        TransactionCSV::Write(transactions, transactionCount);
        AccountCSV::Write(accounts, accountCount);

        std::cout << "Last transaction undone successfully! New Balance: " << account->Balance << " TND\n";
    }


}

#endif
