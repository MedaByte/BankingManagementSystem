#ifndef CSVINITIALIZER_H
#define CSVINITIALIZER_H

#include "OriginPath.h"

#include <fstream>
#include <iostream>
#include <string>

namespace Utils {

    inline bool FileExists(const std::string& path) {
        std::ifstream f(path);
        return f.good();
    }

    inline void CreateFileIfMissing(const std::string& path, const std::string& header) {
        
            std::ofstream file(path, std::ios::trunc);
            if (file.is_open()) {
                file << header;
                file.close();
                std::cout << "Created -> " << path << "\n";
            } else {
                std::cerr << "Error upon Creation: " << path << "\n";
            }
        
    }

    inline void InitializeCSVFiles() {
        const std::string dataFolder = Utils::GetOriginFolder() + "/BackEnd/Data/";

        CreateFileIfMissing(
            dataFolder + "loans.csv",
            "LoanID,Amount,InterestRate,StartDay/StartMonth/StartYear,EndDay/EndMonth/EndYear,Status\n"
        );

        CreateFileIfMissing(
            dataFolder + "transactions.csv",
            "TransactionID,AccountNumber,Type,Amount,Day/Month/Year\n"
        );

        CreateFileIfMissing(
            dataFolder + "accounts.csv",
            "AccountNumber,HolderName,AccountType,IBAN,BranchCode,OpeningDate,Status,Balance\n"
        );

        CreateFileIfMissing(
            dataFolder + "customers.csv",
            "CustomerID,Name,LastName,Address,Phone\n"
        );

        CreateFileIfMissing(
            dataFolder + "employees.csv",
            "Id,Name,LastName,Address,Salary,HireDay/HireMonth/HireYear,BranchCode,Status\n"
        );

        std::cout << "CSVs r goodtogo\n";
    }

}

#endif
