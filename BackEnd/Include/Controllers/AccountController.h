#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H

#include <iostream>
#include "../Models/Account.h"
#include "../Models/Customer.h"
#include "../Models/Loan.h"
#include "../Models/Transaction.h"
#include "../../CSV/AccountCSV.h"

namespace AccountController {

    // Find account by account number in an array | Encontrar uma conta pelo número da conta no array
    inline Account::Account* FindAccount(Account::Account accounts[], int accountCount, const std::string& accountNumber) {
        for(int i = 0; i < accountCount; i++) {
            if(accounts[i].AccountNumber == accountNumber)
                return &accounts[i];
        }
        return nullptr;
    }

    // Display all accounts in an array | Mostrar todas as contas no array
    inline void ViewAccounts(Account::Account accounts[], int accountCount) {
        std::cout << "--- Accounts List ---\n";
        for(int i = 0; i < accountCount; i++) {
            Account::Display(accounts[i]);
            std::cout << "----------------------\n";
        }
    }

    // Change account status and save changes | Mudar o status da conta e salvar alterações
    inline void ChangeStatus(Account::Account* A, const std::string& newStatus, Account::Account accounts[], int accountCount) {
        Account::ChangeStatus(A, newStatus);
        std::cout << "Account " << A->AccountNumber << " status changed to " << newStatus << "\n";

        AccountCSV::Write(accounts, accountCount); // Persist changes to CSV | Persistir alterações no CSV
    }

    // Delete closed accounts from array and save changes | Deletar contas fechadas do array e salvar alterações
    inline void DeleteClosedAccounts(Account::Account accounts[], int& accountCount) {
        int shift = 0;
        for(int i = 0; i < accountCount; i++) {
            if(accounts[i].Status == "closed") {
                shift++;
            } else if(shift > 0) {
                accounts[i - shift] = accounts[i]; // Shift active accounts forward | Mover contas ativas para frente
            }
        }
        accountCount -= shift;
        std::cout << shift << " closed accounts deleted.\n";

        AccountCSV::Write(accounts, accountCount); // Save updated array | Salvar array atualizado
    }

    // Add a new account to a customer and save to CSV | Adicionar uma nova conta a um cliente e salvar no CSV
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
        Customer::AddAccount(C, A); // Link account to customer | Vincular conta ao cliente

        std::cout << "Account created successfully!\n";

        AccountCSV::Write(accounts, accountCount); // Save new account to CSV | Salvar nova conta no CSV
    }

}

#endif
