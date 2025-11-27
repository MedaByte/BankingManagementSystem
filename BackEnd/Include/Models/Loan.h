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
        std::string Id;
        double Amount;
        double InterestRate;
        Date::Date StartDate;
        Date::Date EndDate;
        std::string Status;
        Stack::Stack<Transaction::Transaction> Payments;
    };

    inline Loan Create(
        double Amount,
        double InterestRate,
        int DurationInMonths,
        const std::string& Status = "active",
        std::string Id = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_loan_id.txt", "LOAN"),
        const Date::Date& StartDate = Date::Now()
    ) {
        Date::Date EndDate = Date::AddMonths(StartDate, DurationInMonths);

        Loan NewLoan{
            Id,
            Amount,
            InterestRate,
            StartDate,
            EndDate,
            Status,
            Stack::Create<Transaction::Transaction>()
        };

        std::ofstream File(Utils::GetOriginFolder() + "/BackEnd/Data/loans.csv", std::ios::app);
        File << NewLoan.Id << ","
            << NewLoan.Amount << ","
            << NewLoan.InterestRate << ","
            << Date::GetDay(NewLoan.StartDate) << "/"
            << Date::GetMonth(NewLoan.StartDate) << "/"
            << NewLoan.StartDate.Year << ","
            << Date::GetDay(NewLoan.EndDate) << "/"
            << Date::GetMonth(NewLoan.EndDate) << "/"
            << NewLoan.EndDate.Year << ","
            << NewLoan.Status << "\n";
        File.close();

        return NewLoan;
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
        std::cout << "Id: " << L.Id << "\n";
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
