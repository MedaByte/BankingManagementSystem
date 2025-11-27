#ifndef LOAN_CSV_H
#define LOAN_CSV_H
#include <fstream>
#include <sstream>
#include <string>
#include "../Include/Models/Loan.h"
#include "../Include/Utils/OriginPath.h"

namespace LoanCSV {
    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/loans.csv";
    }

    inline void Write(const Loan::Loan& L) {
        std::ofstream File(GetFilePath(), std::ios::app);
        if(File.is_open()) {
            File << L.Id << "," << L.Amount << "," << L.InterestRate << ","
                    << L.StartDate.Day << "/" << L.StartDate.Month << "/" << L.StartDate.Year << ","
                    << L.EndDate.Day << "/" << L.EndDate.Month << "/" << L.EndDate.Year << ","
                    << L.Status << "\n";
            File.close();
        }
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }
}
#endif
