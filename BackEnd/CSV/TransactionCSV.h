#ifndef TRANSACTION_CSV_H
#define TRANSACTION_CSV_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "../Include/Models/Transaction.h"
#include "../Include/DataStructures/SinglyLinkedList.h"
#include "../Include/Utils/OriginPath.h"

namespace TransactionCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/transactions.csv";
    }

    inline void Write(const Transaction::Transaction& T){
        std::ofstream File(GetFilePath(), std::ios::app);
        if(!File.is_open()) return;

        File << T.TransactionId << ","
                << T.AccountNumber << ","
                << T.Type << ","
                << std::fixed << std::setprecision(2) << T.Amount << ","
                << Date::GetDay(T.Date) << "/"
                << Date::GetMonth(T.Date) << "/"
                << T.Date.Year << "\n";

        File.close();
    }

    inline Singly::List<Transaction::Transaction> ReadAll(){
        auto List = Singly::Create<Transaction::Transaction>();
        std::ifstream File(GetFilePath());
        if(!File.is_open()) return List;

        std::string Line;
        while(std::getline(File, Line)){
            std::stringstream ss(Line);
            std::string id, acc, type, amountStr, dateStr;

            std::getline(ss, id, ',');
            std::getline(ss, acc, ',');
            std::getline(ss, type, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, dateStr, ',');

            double amount = 0.0;
            try {
                if (!amountStr.empty()) amount = std::stod(amountStr);
            } catch(const std::exception& e) {
                std::cerr << "Invalid transaction amount '" << amountStr 
                            << "' for transaction ID " << id << ". Defaulting to 0.\n";
                amount = 0.0;
            }

            int d = 0, m = 0, y = 0;
            sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y);

            Transaction::Transaction T{
                id,
                acc,
                type,
                amount,
                {d, m, y}
            };

            Singly::PushBack(&List, T);
        }

        File.close();
        return List;
    }

    inline void ClearAll() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }
}

#endif
