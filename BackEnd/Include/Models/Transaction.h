#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "../Utils/IdGenerator.h"
#include "../Utils/OriginPath.h"

namespace Transaction {

    struct Transaction {
        std::string TransactionId;     // Unique transaction ID | ID único da transação
        std::string AccountNumber;     // Account linked to transaction | Conta associada à transação
        std::string Type;              // Type: deposit, withdrawal, etc | Tipo: depósito, saque, etc
        double Amount;                 // Transaction amount | Quantia da transação
        Date::Date Date;               // Transaction date | Data da transação
    };

    inline Transaction Create(
        const std::string& AccountNumber,
        const std::string& Type,
        double Amount,
        const Date::Date& D = Date::Now(),
        std::string TransactionId = Utils::GenerateId(
            Utils::GetOriginFolder() + "/BackEnd/Data/last_trans_id.txt",
            "TRANS"
        )
    ) {
        // Create a new transaction | Criar uma nova transação
        return Transaction{
            TransactionId,
            AccountNumber,
            Type,
            Amount,
            D
        };
    }

    inline void Display(const Transaction& T){
        std::cout << "Transaction ID: " << T.TransactionId << "\n";
        std::cout << "Account: " << T.AccountNumber << "\n";
        std::cout << "Type: " << T.Type << "\n";
        std::cout << "Amount: " << std::fixed << std::setprecision(2)
                    << T.Amount << " TND\n";
        std::cout << "Date: " << Date::ToString(T.Date) << "\n";
        // Display transaction details | Mostrar detalhes da transação
    }

}

#endif
