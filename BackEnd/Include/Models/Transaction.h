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
        std::string TransactionId;
        std::string AccountNumber;
        std::string Type;
        double Amount;
        Date::Date Date;
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
    }

    std::ostream& operator<<(std::ostream& os, const Transaction& T){
    os << "[" << T.TransactionId << ", " << T.AccountNumber 
        << ", " << T.Type << ", " << T.Amount << "]";
    return os;
}
}

#endif
