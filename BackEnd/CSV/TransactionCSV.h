#ifndef TRANSACTIONCSV_H
#define TRANSACTIONCSV_H

#include <fstream>
#include <sstream>
#include "../Models/Transaction.h"
#include "../Models/Date.h"
#include "../Utils/OriginPath.h"

namespace TransactionCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline void Load(Transaction::Transaction transactions[], int& count, const std::string& filename = "transactions.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tmp;

            Transaction::Transaction T;

            std::getline(ss, T.TransactionId, ',');
            std::getline(ss, T.AccountNumber, ',');
            std::getline(ss, T.Type, ',');

            std::getline(ss, tmp, ',');
            T.Amount = std::stod(tmp);

            std::getline(ss, tmp, ',');
            T.Date = Date::FromString(tmp);

            transactions[count++] = T;
        }
    }

}

#endif
