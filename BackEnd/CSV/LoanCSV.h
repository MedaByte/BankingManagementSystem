#ifndef LOANCSV_H
#define LOANCSV_H

#include <fstream>
#include <sstream>
#include "../Models/Loan.h"
#include "../Models/Date.h"
#include "../Utils/OriginPath.h"

namespace LoanCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline void Load(Loan::Loan loans[], int& count, const std::string& filename = "loans.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tmp;

            Loan::Loan L;

            std::getline(ss, L.Id, ',');
            std::getline(ss, L.AccountId, ',');

            std::getline(ss, tmp, ',');
            L.Amount = std::stod(tmp);

            std::getline(ss, tmp, ',');
            L.InterestRate = std::stod(tmp);

            std::getline(ss, tmp, ',');
            L.PaidAmount = std::stod(tmp);

            std::getline(ss, tmp, ',');
            L.RemainingAmount = std::stod(tmp);

            std::getline(ss, tmp, ',');
            L.StartDate = Date::FromString(tmp);

            std::getline(ss, tmp, ',');
            L.EndDate = Date::FromString(tmp);

            std::getline(ss, L.Status, ',');

            // Payments stack cannot be loaded — initialize empty
            L.Payments = Stack::Create<Transaction::Transaction>();

            loans[count++] = L;
        }
    }

}

#endif
