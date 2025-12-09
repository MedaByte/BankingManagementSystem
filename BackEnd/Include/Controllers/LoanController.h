#ifndef LOAN_CONTROLLER_H
#define LOAN_CONTROLLER_H

#include <iostream>
#include "../Models/Loan.h"
#include "../Models/Account.h"
#include "../Models/Customer.h"
#include "../Models/Transaction.h"

namespace LoanController {

    template<typename T>
    // Find loan by ID in a customer's accounts | Encontrar loan pelo ID nas contas de um customer
    inline Loan::Loan* FindLoan(Customer::Customer* C, const std::string& loanId) {
        for(auto node = C->Accounts.Head; node; node = node->Next) {
            for(auto loanNode = node->Data.Loans.Head; loanNode; loanNode = loanNode->Next) {
                if(loanNode->Data.Id == loanId)
                    return &loanNode->Data;
            }
        }
        return nullptr;
    }

    // Display all loans of a customer | Mostrar todos os loans de um customer
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

    // Add loan to an account | Adicionar loan a uma account
    inline void AddLoan(Account::Account* A, const Loan::Loan& L) {
        Account::AddLoan(A, L);
        std::cout << "Loan " << L.Id << " added to account " << A->AccountNumber << "\n";
        // Log addition | Log de adição
    }

    // Change loan status | Alterar status do loan
    inline void ChangeLoanStatus(Loan::Loan* L, const std::string& status) {
        Loan::ChangeStatus(L, status);
        std::cout << "Loan " << L->Id << " status changed to " << status << "\n";
        // Log status change | Log da alteração de status
    }

    // Delete all completed loans from customer accounts | Deletar todos os loans com status 'completed' das contas do customer
    inline void DeleteCompletedLoans(Loan::Loan loans[], int& loanCount) {
        std::cerr << "hello";

        Loan::Loan completedLoans[loanCount];
        int posição = 0;
        for (int i = 0; i<loanCount;){
            if (loans[i].Status == "completed"){
                completedLoans[posição++] = loans[i];
                for (int j = i; j<loanCount-1;++j){
                    loans[j] = loans[j+1];
                }
                --loanCount;
            }
            else{
                ++i;
            }
        }

        LoanCSV::Write(loans, loanCount);
    }

    // Add payment to a loan | Adicionar pagamento a um loan
    inline void AddPayment(Loan::Loan* L, const Transaction::Transaction& T) {
        Loan::AddPayment(L, T);
        std::cout << "Payment of " << T.Amount << " TND applied to loan " << L->Id << "\n";
        // Log payment | Log do pagamento
    }

    // Undo last payment of a loan | Desfazer último pagamento de um loan
    inline void UndoLastPayment(Loan::Loan* L) {
        Loan::UndoLastPayment(L);
        std::cout << "Last payment undone for loan " << L->Id << "\n";
        // Log undo | Log do desfazer
    }

}

#endif
