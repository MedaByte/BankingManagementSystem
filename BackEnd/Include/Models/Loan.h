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
        std::string Id;
        std::string AccountId;      // 🔥 NEW — Loan belongs to an Account
        double Amount;
        double InterestRate;
        double PaidAmount;          // 🔥 NEW
        double RemainingAmount;     // 🔥 NEW
        Date::Date StartDate;
        Date::Date EndDate;
        std::string Status;

        Stack::Stack<Transaction::Transaction> Payments;
    };

    inline Loan Create(
        const std::string& AccountId,
        double Amount,
        double InterestRate,
        int DurationInMonths,
        const std::string& Status = "active",
        std::string Id = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_loan_id.txt", "LOAN"),
        const Date::Date& StartDate = Date::Now()
    ) {
        Date::Date EndDate = Date::AddMonths(StartDate, DurationInMonths);

        Loan L{
            Id,
            AccountId,                 // link loan → account
            Amount,
            InterestRate,
            0.0,                       // PaidAmount
            Amount,                    // RemainingAmount
            StartDate,
            EndDate,
            Status,
            Stack::Create<Transaction::Transaction>()
        };

        return L;
    }

    inline void AddPayment(Loan* L, const Transaction::Transaction& T){
        Stack::Push(&L->Payments, T);
        L->PaidAmount += T.Amount;
        L->RemainingAmount -= T.Amount;
        if(L->RemainingAmount < 0) L->RemainingAmount = 0;
    }

    inline void UndoLastPayment(Loan* L){
        if (Stack::IsEmpty(L->Payments)) return;
        auto last = Stack::Top(L->Payments);
        L->PaidAmount -= last.Amount;
        L->RemainingAmount += last.Amount;
        Stack::Pop(&L->Payments);
    }

    inline void ChangeStatus(Loan* L, const std::string& NewStatus){
        L->Status = NewStatus;
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
    }

    inline std::ostream& operator<<(std::ostream& os, const Loan& loan) {
        os << "[Loan ID: " << loan.Id
            << ", Amount: " << loan.Amount
            << ", Interest: " << loan.InterestRate
            << ", Start: " << loan.StartDate.Day << "/" << loan.StartDate.Month << "/" << loan.StartDate.Year
            << ", End: " << loan.EndDate.Day << "/" << loan.EndDate.Month << "/" << loan.EndDate.Year << " months]";
        return os;
    }
}

#endif
