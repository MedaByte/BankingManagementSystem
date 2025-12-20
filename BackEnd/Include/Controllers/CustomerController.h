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


namespace CustomerController
{

    // Find a customer by ID | Encontrar um cliente pelo ID
    inline Customer::Customer *FindCustomer(Customer::Customer customers[], int customerCount, const std::string &Id)
    {
        for (int i = 0; i < customerCount; ++i)
            if (customers[i].Id == Id)
                return &customers[i];
        return nullptr;
    }

    // Create a new customer | Criar um novo cliente
    inline Customer::Customer &CreateCustomer(
        Customer::Customer customers[],
        int &customerCount,
        const std::string &name,
        const std::string &lastName,
        const std::string &address,
        const std::string &phone)
    {
        if (customerCount >= 100)
        {
            std::cerr << "Customer limit reached!\n";
            throw std::runtime_error("Overflow");
        }

        Customer::Customer C = Customer::Create(name, lastName, address, phone);
        customers[customerCount] = C;
        std::cout<<C.Id<<std::endl ;

        CustomerCSV::Write(customers, customerCount + 1); // Save customer array to CSV | Salvar array de clientes no CSV

        return customers[customerCount++];
    }

    // Create a new account for a customer | Criar uma nova conta para um cliente
    inline Account::Account &CreateAccount(
        Account::Account accounts[],
        int &accountCount,
        Customer::Customer *C,
        const std::string &type,
        const std::string &pin,
        Customer::Customer customers[],
        int customerCount)
    {
        if (accountCount >= 200)
        {
            std::cerr << "Account limit reached!\n";
            throw std::runtime_error("Overflow");
        }

        Account::Account A = Account::Create(
            C->Name + " " + C->LastName,
            type,
            pin,
            "active",
            C->Id);

        Customer::AddAccount(C, A); // Link account to customer | Vincular conta ao cliente
        accounts[accountCount] = A;

        AccountCSV::Write(accounts, accountCount + 1); // Save accounts array to CSV | Salvar array de contas no CSV
        CustomerCSV::Write(customers, customerCount);  // Save customers to CSV | Salvar clientes no CSV

        return accounts[accountCount++];
    }

    // View all accounts of a customer | Mostrar todas as contas de um cliente
    inline void ViewAccounts(Customer::Customer *C)
    {
        std::cout << "--- Accounts for " << C->Name << " " << C->LastName << " ---\n";
        auto node = C->Accounts.Head;
        while (node)
        {
            Account::Display(node->Data);
            std::cout << "-----------------------\n";
            node = node->Next;
        }
    }

    // View all loans of a customer | Mostrar todos os loans de um cliente
    inline void ViewLoans(Customer::Customer *C)
    {
        std::cout << "--- Loans for " << C->Name << " " << C->LastName << " ---\n";
        auto accNode = C->Accounts.Head;
        while (accNode)
        {
            auto loanNode = accNode->Data.Loans.Head;
            while (loanNode)
            {
                Loan::Display(loanNode->Data);
                std::cout << "-----------------------\n";
                loanNode = loanNode->Next;
            }
            accNode = accNode->Next;
        }
    }

    // Request a loan for a customer | Solicitar um loan para um cliente
    inline void RequestLoan(Loan::Loan loanRequests[], int &loanRequestCount,
                            Account::Account accounts[], int accountCount,
                            string AccNum,
                            double amount,
                            int duration,
                            string type)
    {

        Account::Account *account = nullptr;
        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].AccountNumber == AccNum)
            {
                account = &accounts[i];
            }
        }

        Loan::Loan L = Loan::Create(account->AccountNumber, amount, 0.025, duration, "Waiting For Response", type);
        loanRequests[loanRequestCount++] = L;

        LoanCSV::Write(loanRequests, loanRequestCount);
    }

    // Deposit money into a customer's account | Depositar dinheiro em uma conta do cliente
    inline void Deposit(int amount,
                        string accNum,
                        Account::Account accounts[],
                        int accountCount,
                        Transaction::Transaction transactions[],
                        int &transactionCount)
    {

        Account::Account *account;
        for (int i = 0; i < accountCount; ++i)
        {
            if (accounts[i].AccountNumber == accNum)
            {
                account = &accounts[i];
            }
        }

        Transaction::Transaction T = Transaction::Create(accNum, "deposit", amount);
        transactions[transactionCount++] = T;
        Account::AddTransaction(account, T);

        for (int i = 0; i < accountCount; ++i)
        {
            if (accounts[i].CustomerId == account->CustomerId && accounts[i].AccountNumber == accNum)
            {
                accounts[i] = *account;
                Stack::Push(&accounts[i].DailyTransactions, T); // Add to daily transactions stack | Adicionar na stack de transações diárias
            }
        }

        TransactionCSV::Write(transactions, transactionCount); // Persist transactions | Persistir transações
        AccountCSV::Write(accounts, accountCount);             // Persist accounts | Persistir contas
    }

    // Withdraw money from a customer's account | Sacar dinheiro de uma conta do cliente
    inline void Withdraw(double amount,
                         string accNum,
                         Account::Account accounts[],
                         int accountCount,
                         Transaction::Transaction transactions[],
                         int &transactionCount)
    {

        Account::Account *account = nullptr;
        for (int i = 0; i < accountCount; ++i)
        {
            if (accounts[i].AccountNumber == accNum)
            {
                account = &accounts[i];
            }
        }

        account->Balance -= amount; // Update balance | Atualizar saldo
        Transaction::Transaction T = Transaction::Create(accNum, "withdrawal", amount);
        transactions[transactionCount++] = T;
        Stack::Push(&account->DailyTransactions, T); // Add to daily transactions stack | Adicionar na stack de transações diárias

        for (int i = 0; i < accountCount; ++i)
        {
            if (accounts[i].AccountNumber == accNum)
            {
                accounts[i] = *account; // Copy updated balance and stack | Copiar saldo e stack atualizados
                break;
            }
        }

        std::cerr << "4";
        TransactionCSV::Write(transactions, transactionCount);
        AccountCSV::Write(accounts, accountCount);

        std::cerr << "5";
    }

    // View all daily transactions of a customer's account | Mostrar todas as transações diárias de uma conta
    inline void ViewTransactions(Customer::Customer *C)
    {
        std::string accNum;
        std::cout << "Enter Account Number: ";
        std::cin >> accNum;
        Account::Account *account = Customer::FindAccount(C, accNum);
        if (!account)
        {
            std::cout << "Account not found!\n";
            return;
        }

        std::cout << "--- Transactions ---\n";
        auto node = account->DailyTransactions.List.Head;
        while (node)
        {
            Transaction::Display(node->Data);
            std::cout << "-----------------\n";
            node = node->Next;
        }
    }

    // Undo the last transaction for a customer's account | Desfazer a última transação de uma conta do cliente
    inline void UndoTransaction(string accNum,
                                Account::Account accounts[],
                                int accountCount,
                                Transaction::Transaction transactions[],
                                int &transactionCount)
    {

        Account::Account *account = nullptr;
        int Indx;
        for (int i = 0; i < accountCount; ++i)
        {
            if (accounts[i].AccountNumber == accNum)
            {
                account = &accounts[i];
                Indx = i;
                // this is right
            }
        }

        if (Stack::IsEmpty(account->DailyTransactions))
        {
            return;
        }

        Transaction::Transaction lastTx = Stack::Top(account->DailyTransactions);
        Stack::Pop(&account->DailyTransactions); // Remove last transaction | Remover última transação
        // Reverse transaction effect on balance | Reverter efeito da transação no saldo
        if (lastTx.Type == "deposit" || lastTx.Type == "loanDeposit")
        {
            account->Balance -= lastTx.Amount;
        }
        else if (lastTx.Type == "withdrawal")
            account->Balance += lastTx.Amount;

        accounts[Indx] = *account;

        // Remove transaction from global transactions array | Remover transação do array global
        bool removed = false;
        for (int i = transactionCount - 1; i >= 0; --i)
        {
            if (transactions[i].TransactionId == lastTx.TransactionId)
            {
                for (int j = i; j < transactionCount - 1; ++j)
                    transactions[j] = transactions[j + 1];
                --transactionCount;
                removed = true;
                break;
            }
        }

        if (transactionCount == 0)
        {
            transactions = nullptr;
        }
        TransactionCSV::Write(transactions, transactionCount);
        AccountCSV::Write(accounts, accountCount);
    }

}

#endif
