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
        std::string AccountNumber;     // Account number | Número da account
        std::string AccountType;       // Type of account | Tipo da account
        std::string IBAN;              // IBAN code | Código IBAN
        std::string BranchCode;        // Branch code | Código da branch
        std::string HolderName;        // Account holder | Dono da account
        Date::Date OpeningDate;        // Opening date | Data de abertura
        std::string Status;            // Account status | Status da account
        double Balance;                // Balance | Saldo
        std::string Note;              // Note about the account | nota sobra a account
        std::string Image;             // image of the account holder | imagem do dono da account
        std::string CustomerId;        // Customer ID | ID do customer

        Doubly::List<Loan::Loan> Loans;                            // Loan list | Lista de loans
        Stack::Stack<Transaction::Transaction> DailyTransactions;  // Daily transactions | Transações diárias
    };

    inline std::string GenerateIBAN(const std::string& BranchCode, const std::string& AccountNumber) {
        return "TN00" + BranchCode + AccountNumber;
        // Generate IBAN | Gerar IBAN
    }

    inline Account Create(
        const std::string& HolderName,
        const std::string& AccountType,
        const std::string& BranchCode,
        const std::string& Status,
        const std::string CustomerId,
        const std::string& Note = "Bread",
        const std::string& AccountNumber  = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_account_id.txt", "ACC"),
        const Date::Date& OpeningDate = Date::Now(),
        double Balance = 0.0,
        const std::string& Image = "default"
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
            Note,
            Image,
            CustomerId,
            Doubly::Create<Loan::Loan>(),                   // Init loans | Inicializar loans
            Stack::Create<Transaction::Transaction>()       // Init stack | Inicializar stack
        };

        return NewAccount; // Return new account | Retornar nova account
    }

    inline void AddLoan(Account* A, const Loan::Loan& L) {
        Doubly::PushBack(&A->Loans, L);
        // Add loan | Adicionar loan
    }

    inline Loan::Loan* FindLoan(Account* A, std::string Id) {
        auto Loan = Doubly::FindByID(A->Loans, Id);
        if (Loan) return &Loan->Data;  // Return found loan | Retornar loan encontrado
        std::cout << "Loan Not Found: " << Id;
        return nullptr;                // Loan not found | Loan não encontrado
    }

    inline void RemoveAt(Account* A, int Pos) {
        Doubly::RemoveAt(&A->Loans, Pos);
        // Remove at position | Remover na posição
    }

    inline void AddTransaction(Account* A, const Transaction::Transaction& T) {
        Stack::Push(&A->DailyTransactions, T); // Add transaction | Adicionar transação

        if (T.Type == "deposit") 
            A->Balance += T.Amount;        // Deposit | Depósito
        else if (T.Type == "withdrawal") 
            A->Balance -= T.Amount;        // Withdrawal | Retirada
    }

    inline void UndoLastTransaction(Account* A) {
        if (Stack::IsEmpty(A->DailyTransactions)) return; 
        // If empty, nothing to undo | Se vazio, nada para desfazer

        Transaction::Transaction Last = Stack::Top(A->DailyTransactions);

        if (Last.Type == "deposit") 
            A->Balance -= Last.Amount;     // Undo deposit | Desfazer depósito
        else if (Last.Type == "withdrawal") 
            A->Balance += Last.Amount;     // Undo withdrawal | Desfazer retirada

        Stack::Pop(&A->DailyTransactions);  // Remove from stack | Remover da stack
    }

    inline void ChangeStatus(Account* A, const std::string& NewStatus) {
        A->Status = NewStatus;
        // Change status | Mudar status
    }

    inline void Display(const Account& A) {
        std::cout << "AccountNumber: " << A.AccountNumber << "\n";
        std::cout << "HolderName: " << A.HolderName << "\n";
        std::cout << "AccountType: " << A.AccountType << "\n";
        std::cout << "IBAN: " << A.IBAN << "\n";
        std::cout << "BranchCode: " << A.BranchCode << "\n";
        std::cout << "OpeningDate: " 
            << Date::GetDay(A.OpeningDate) << "/"
            << Date::GetMonth(A.OpeningDate) << "/"
            << A.OpeningDate.Year << "\n";
        std::cout << "Status: " << A.Status << "\n";
        std::cout << "CustomerId: " << A.CustomerId << "\n";
        std::cout << "Balance: " << std::fixed << std::setprecision(2) << A.Balance << " TND\n";
        std::cout << "Loans: " << A.Loans.Size << "\n";
        std::cout << "Daily Transactions: " << A.DailyTransactions.List.Size << "\n";
        // Display account details | Mostrar detalhes da account
    }

}

#endif
