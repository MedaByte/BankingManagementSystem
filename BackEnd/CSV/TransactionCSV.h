#ifndef TRANSACTION_CSV_H
#define TRANSACTION_CSV_H

#include <fstream>
#include <sstream>
#include <iomanip>
#include "../Include/Models/Transaction.h"
#include "../Include/DataStructures/SinglyLinkedList.h"
#include "../Include/Utils/OriginPath.h"

namespace TransactionCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/transactions.csv";
    }

    inline void WriteHeader() {
        std::ofstream File(GetFilePath(), std::ios::app);
        File.seekp(0, std::ios::end);
        if (File.tellp() == 0) {
            File << "Id,Account,Type,Amount,Date\n";
        }
    }

    inline void Write(const Transaction::Transaction& T) {
        WriteHeader();

        std::ofstream File(GetFilePath(), std::ios::app);
        if (!File.is_open()) return;

        File << T.TransactionId << ","
             << T.AccountNumber << ","
             << T.Type << ","
             << std::fixed << std::setprecision(2) << T.Amount << ","
             << T.Date.Day << "/" << T.Date.Month << "/" << T.Date.Year
             << "\n";
    }

    inline Singly::List<Transaction::Transaction> ReadAll() {
        auto list = Singly::Create<Transaction::Transaction>();

        std::ifstream File(GetFilePath());
        if (!File.is_open()) return list;

        std::string Line;
        std::getline(File, Line); // skip header

        while (std::getline(File, Line)) {
            std::stringstream ss(Line);
            std::string id, acc, type, amountStr, dateStr;

            std::getline(ss, id, ',');
            std::getline(ss, acc, ',');
            std::getline(ss, type, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, dateStr, ',');

            double amount = amountStr.empty() ? 0.0 : std::stod(amountStr);

            int d=0, m=0, y=0;
            sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y);

            Transaction::Transaction T{
                id, acc, type, amount, {d, m, y}
            };

            Singly::PushBack(&list, T);
        }

        return list;
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
    }
}

#endif
