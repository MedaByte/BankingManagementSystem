#ifndef ACCOUNTCSV_H
#define ACCOUNTCSV_H

#include <fstream>
#include <sstream>
#include "../Models/Account.h"
#include "../Models/Date.h"
#include "../Utils/OriginPath.h"

namespace AccountCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline void Load(Account::Account accounts[], int& count, const std::string& filename = "accounts.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tmp;

            Account::Account A;

            std::getline(ss, A.AccountNumber, ',');
            std::getline(ss, A.AccountType, ',');
            std::getline(ss, A.IBAN, ',');
            std::getline(ss, A.BranchCode, ',');
            std::getline(ss, A.HolderName, ',');

            std::getline(ss, tmp, ',');
            A.OpeningDate = Date::FromString(tmp);

            std::getline(ss, A.Status, ',');

            std::getline(ss, tmp, ',');
            A.Balance = std::stod(tmp);

            std::getline(ss, A.CustomerId, ',');

            A.Loans = Doubly::Create<Loan::Loan>();
            A.DailyTransactions = Stack::Create<Transaction::Transaction>();

            accounts[count++] = A;
        }
    }
}

#endif
