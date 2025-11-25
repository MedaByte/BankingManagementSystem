#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../DataStructures/DoublyLinkedList.h"
#include "../DataStructures/Stack.h"
#include "../Utils/OriginPath.h"
#include "../Utils/IdGenerator.h"
#include "Transaction.h"
#include "Date.h"

namespace Loan {

    struct Loan {
        std::string LoanID;
        double Amount;
        double InterestRate;
        Date::Date StartDate;
        Date::Date EndDate;
        std::string Status;
        Stack::Stack<Transaction::Transaction> Payments;
    };

    inline Loan Create(
        std::string LoanID = Utils::GenerateId(Utils::GetOriginFolder() + "BackEnd/Data/last_loan_id.txt", "LOAN"),
        double Amount,
        double InterestRate,
        int DurationInMonths,
        const Date::Date& StartDate = Date::Now(),
        const std::string& Status = "active"
    ){

        Date::Date EndDate = Date::AddMonths(StartDate, DurationInMonths);
        return Loan{
            LoanID,
            Amount,
            InterestRate,
            StartDate,
            EndDate,
            Status,
            Stack::Create<Transaction::Transaction>()
        };
    }

    inline void AddPayment(Loan* L, const Transaction::Transaction& T){
        Stack::Push(&L->Payments, T);
    }

    inline Transaction::Transaction* LastPayment(Loan* L){
        if (Stack::IsEmpty(L->Payments)) return nullptr;
        return &Stack::Top(L->Payments);
    }

    inline void UndoLastPayment(Loan* L){
        if (Stack::IsEmpty(L->Payments)) return;
        Stack::Pop(&L->Payments);
    }

    inline void ChangeStatus(Loan* L, const std::string& NewStatus){
        L->Status = NewStatus;
    }

    inline void Display(const Loan& L){
        std::cout << "LoanID: " << L.LoanID << "\n";
        std::cout << "Amount: " << std::fixed << std::setprecision(2) << L.Amount << " TND\n";
        std::cout << "InterestRate: " << L.InterestRate * 100 << "%\n";
        std::cout << "StartDate: " << Date::GetDay(L.StartDate) << "/" 
                    << Date::GetMonth(L.StartDate) << "/" << L.StartDate.Year << "\n";
        std::cout << "EndDate: " << Date::GetDay(L.EndDate) << "/" 
                    << Date::GetMonth(L.EndDate) << "/" << L.EndDate.Year << "\n";
        std::cout << "Status: " << L.Status << "\n";
        std::cout << "Number of Payments: " << L.Payments.List.Size << "\n";
    }

}

#endif
