#ifndef LOAN_CONTROLLER_H
#define LOAN_CONTROLLER_H

#include <iostream>
#include "../Models/Loan.h"
#include "../Models/Account.h"
#include "../Models/Customer.h"
#include "../Models/Transaction.h"

namespace LoanController {

    // Find loan by ID in a customer's accounts
    inline Loan::Loan* FindLoan(Customer::Customer* C, const std::string& loanId) {
        for(auto node = C->Accounts.Head; node; node = node->Next) {
            for(auto loanNode = node->Data.Loans.Head; loanNode; loanNode = loanNode->Next) {
                if(loanNode->Data.Id == loanId)
                    return &loanNode->Data;
            }
        }
        return nullptr;
    }

    // Display all loans of a customer
    inline void ViewLoans(Customer::Customer* C) {
        std::cout << "--- Loans for " << C->Name << " " << C->LastName << " ---\n";
        for(auto node = C->Accounts.Head; node; node = node->Next) {
            Account::Account& acc = node->Data;
            for(auto loanNode = acc.Loans.Head; loanNode; loanNode = loanNode->Next) {
                Loan::Display(loanNode->Data);
                std::cout << "----------------------\n";
            }
        }
    }

    // Add loan to an account
    inline void AddLoan(Account::Account* A, const Loan::Loan& L) {
        Account::AddLoan(A, L);
        std::cout << "Loan " << L.Id << " added to account " << A->AccountNumber << "\n";
    }

    // Change loan status
    inline void ChangeLoanStatus(Loan::Loan* L, const std::string& status) {
        Loan::ChangeStatus(L, status);
        std::cout << "Loan " << L->Id << " status changed to " << status << "\n";
    }

    // Delete all completed loans from customer accounts
    inline void DeleteCompletedLoans(Customer::Customer* C) {
        for(auto node = C->Accounts.Head; node; node = node->Next) {
            auto& loans = node->Data.Loans;
            auto current = loans.Head;
            int pos = 0;
            while(current) {
                auto nextNode = current->Next;
                if(current->Data.Status == "completed") {
                    Account::RemoveAt(&node->Data, pos);
                    std::cout << "Loan " << current->Data.Id << " deleted.\n";
                    // pos does not increase because list size shrinks
                } else {
                    pos++;
                }
                current = nextNode;
            }
        }
    }

    // Add payment to a loan
    inline void AddPayment(Loan::Loan* L, const Transaction::Transaction& T) {
        Loan::AddPayment(L, T);
        std::cout << "Payment of " << T.Amount << " TND applied to loan " << L->Id << "\n";
    }

    // Undo last payment of a loan
    inline void UndoLastPayment(Loan::Loan* L) {
        Loan::UndoLastPayment(L);
        std::cout << "Last payment undone for loan " << L->Id << "\n";
    }
}

#endif
