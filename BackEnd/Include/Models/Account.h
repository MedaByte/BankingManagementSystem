#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../DataStructures/DoublyLinkedList.h"
#include "../DataStructures/Stack.h"
#include "../Utils/IdGenerator.h"
#include "../Utils/OriginPath.h"
#include "Loan.h"
#include "Transaction.h"
#include "Date.h"
#include <fstream>

namespace Account {
    struct Account {
        std::string AccountNumber;
        std::string AccountType;
        std::string IBAN;
        std::string BranchCode;
        std::string HolderName;
        Date::Date OpeningDate;
        std::string Status;
        double Balance;

        Doubly::List<Loan::Loan> Loans;
        Stack::Stack<Transaction::Transaction> DailyTransactions;
    };

    inline std::string GenerateIBAN(const std::string& BranchCode, const std::string& AccountNumber) {
        return "TN00" + BranchCode + AccountNumber;
    }


	inline Account Create(
		const std::string& HolderName,
		const std::string& AccountType,
		const std::string& BranchCode,
		const std::string& Status,
		const std::string& AccountNumber  = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_account_id.txt", "ACC"),
		const Date::Date& OpeningDate = Date::Now(),
		double Balance = 0.0
	){
		std::string IBAN = GenerateIBAN(BranchCode, AccountNumber);

		Account NewAccount{
			AccountNumber,
			AccountType,
			IBAN,
			BranchCode,
			HolderName,
			OpeningDate,
			Status,
			Balance,
			Doubly::Create<Loan::Loan>(),
			Stack::Create<Transaction::Transaction>()
		};

		return NewAccount;
	}

	inline void AddLoan(Account* A, const Loan::Loan& L){
		Doubly::PushBack(&A->Loans, L);
	}

	inline Loan::Loan* FindLoan(Account* A, std::string Id){
		auto Loan = Doubly::FindByID(A->Loans, Id);
		if (Loan) return &Loan->Data;
        std::cout << "Loan Not Found: " << Id;
		return nullptr;
	}

	inline void RemoveAt(Account* A, int Pos){
		Doubly::RemoveAt(&A->Loans, Pos);
	}

	inline void AddTransaction(Account* A, const Transaction::Transaction& T){
		Stack::Push(&A->DailyTransactions, T);
		if (T.Type == "deposit") A->Balance += T.Amount;
		else if (T.Type == "withdrawal") A->Balance -= T.Amount;
	}

	inline void UndoLastTransaction(Account* A){
		if (Stack::IsEmpty(A->DailyTransactions)) return;
		Transaction::Transaction Last = Stack::Top(A->DailyTransactions);
		if (Last.Type == "deposit") A->Balance -= Last.Amount;
		else if (Last.Type == "withdrawal") A->Balance += Last.Amount;
		Stack::Pop(&A->DailyTransactions);
	}

	inline void ChangeStatus(Account* A, const std::string& NewStatus){
		A->Status = NewStatus;
	}

	inline void Display(const Account& A){
		std::cout << "AccountNumber: " << A.AccountNumber << "\n";
		std::cout << "HolderName: " << A.HolderName << "\n";
		std::cout << "AccountType: " << A.AccountType << "\n";
		std::cout << "IBAN: " << A.IBAN << "\n";
		std::cout << "BranchCode: " << A.BranchCode << "\n";
		std::cout << "OpeningDate: " << Date::GetDay(A.OpeningDate)
				    << "/" << Date::GetMonth(A.OpeningDate)
				    << "/" << A.OpeningDate.Year << "\n";
		std::cout << "Status: " << A.Status << "\n";
		std::cout << "Balance: " << std::fixed << std::setprecision(2) << A.Balance << " TND\n";
		std::cout << "Loans: " << A.Loans.Size << "\n";
		std::cout << "Daily Transactions: " << A.DailyTransactions.List.Size << "\n";
	}

	std::ostream& operator<<(std::ostream& os, const Account& A){
    os << "[" << A.AccountNumber << ", " 
		<< A.HolderName << ", " 
		<< A.AccountType << ", " 
		<< A.Balance << "]";
    return os;
}
}

#endif
