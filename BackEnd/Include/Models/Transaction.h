#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "../Utils/OriginPath.h"
#include "../Utils/IdGenerator.h"

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
        std::string TransactionId = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_trans_id.txt", "TRANS")
    ) {
        Transaction NewTransaction{
            TransactionId,
            AccountNumber,
            Type,
            Amount,
            D
        };

        std::ofstream File(Utils::GetOriginFolder() + "/BackEnd/Data/Transactions.csv", std::ios::app);
        if(File.is_open()) {
            File << NewTransaction.TransactionId << ","
                << NewTransaction.AccountNumber << ","
                << NewTransaction.Type << ","
                << std::fixed << std::setprecision(2) << NewTransaction.Amount << ","
                << Date::GetDay(NewTransaction.Date) << "/"
                << Date::GetMonth(NewTransaction.Date) << "/"
                << NewTransaction.Date.Year << "\n";
            File.close();
        }

        return NewTransaction;
    }

    inline void Display(const Transaction& T){
        std::cout << "Transaction ID: " << T.TransactionId << "\n";
        std::cout << "Account: " << T.AccountNumber << "\n";
        std::cout << "Type: " << T.Type << "\n";
        std::cout << "Amount: " << std::fixed << std::setprecision(2) 
                    << T.Amount << " TND\n";
        std::cout << "Date: " << Date::ToString(T.Date) << "\n";
    }

}

#endif
