#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../DataStructures/Stack.h"
#include "../Utils/IdGenerator.h"
#include "../Utils/OriginPath.h"
#include "Transaction.h"
#include "Date.h"

namespace Loan {

    struct Loan {
        std::string Id;                // Loan ID | ID do loan
        std::string AccountId;         // Account this loan belongs to | Conta à qual o loan pertence
        double Amount;                 // Loan amount | Quantia do loan
        double InterestRate;           // Interest rate | Taxa de juros
        double PaidAmount;             // Amount already paid | Quantia já paga
        double RemainingAmount;        // Remaining amount | Quantia restante
        Date::Date StartDate;          // Start date | Data de início
        Date::Date EndDate;            // End date | Data de fim
        std::string Status;            // Status (active/closed) | Status (ativo/encerrado)
        std::string type;              // Type of loan | Tipo do loan

        Stack::Stack<Transaction::Transaction> Payments; // Stack of payments | Pilha de pagamentos
    };

    inline Loan Create(
        const std::string& AccountId,
        double Amount,
        double InterestRate,
        int DurationInMonths,
        const std::string& Status = "active",
        std::string type = "general",
        std::string Id = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_loan_id.txt", "LOAN"),
        const Date::Date& StartDate = Date::Now()
    ) {
        Date::Date EndDate = Date::AddMonths(StartDate, DurationInMonths);
        // Calculate end date | Calcular data de fim

        Loan L{
            Id,
            AccountId,
            Amount,
            InterestRate,
            0.0,            // PaidAmount | Quantia paga inicial
            Amount,         // RemainingAmount | Quantia restante inicial
            StartDate,
            EndDate,
            Status,
            type,
            Stack::Create<Transaction::Transaction>()
        };

        return L; // Return new loan | Retornar novo loan
    }

    inline void AddPayment(Loan* L, const Transaction::Transaction& T){
        Stack::Push(&L->Payments, T);
        L->PaidAmount += T.Amount;
        L->RemainingAmount -= T.Amount;
        if(L->RemainingAmount < 0) L->RemainingAmount = 0;
        // Add payment and update amounts | Adicionar pagamento e atualizar quantias
    }

    inline void UndoLastPayment(Loan* L){
        if (Stack::IsEmpty(L->Payments)) return;
        auto last = Stack::Top(L->Payments);
        L->PaidAmount -= last.Amount;
        L->RemainingAmount += last.Amount;
        Stack::Pop(&L->Payments);
        // Undo last payment | Desfazer último pagamento
    }

    inline void ChangeStatus(Loan* L, const std::string& NewStatus){
        L->Status = NewStatus;
        // Change loan status | Alterar status do loan
    }

    inline void Display(const Loan& L){
        std::cout << "Loan ID: " << L.Id << "\n";
        std::cout << "Account: " << L.AccountId << "\n";
        std::cout << "Amount: " << L.Amount << " TND\n";
        std::cout << "Paid: " << L.PaidAmount << " TND\n";
        std::cout << "Remaining: " << L.RemainingAmount << " TND\n";
        std::cout << "Interest Rate: " << (L.InterestRate * 100) << "%\n";
        std::cout << "Start Date: " 
                    << L.StartDate.Day << "/" << L.StartDate.Month << "/" << L.StartDate.Year << "\n";
            std::cout << "End Date: " 
                    << L.EndDate.Day << "/" << L.EndDate.Month << "/" << L.EndDate.Year << "\n";
        std::cout << "Status: " << L.Status << "\n";
        std::cout << "Payments Count: " << L.Payments.List.Size << "\n";
        // Display loan details | Mostrar detalhes do loan
    }

}

#endif
