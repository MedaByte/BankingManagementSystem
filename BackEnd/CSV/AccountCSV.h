#ifndef ACCOUNTCSV_H
#define ACCOUNTCSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "../Include/Models/Account.h"
#include "../Include/Models/Date.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/Models/Customer.h"

namespace AccountCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    // Helper: trim
    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load accounts. Optionally link accounts to customers if customers != nullptr and customerCountPtr != nullptr
    inline void Load(
        Account::Account accounts[],
        int& count,
        Customer::Customer* customers = nullptr,
        int* customerCountPtr = nullptr,
        const std::string& filename = "accounts.csv"
    ) {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        // Optionally read header line
        if (!std::getline(file, line)) return;
        // If first line looks like header (contains non-digit field names), skip it.
        std::istringstream peek(line);
        std::string firstTok;
        std::getline(peek, firstTok, ',');
        bool isHeader = (firstTok.find_first_not_of("0123456789") != std::string::npos);
        if (!isHeader) {
            // first line is data -> process it below
            file.clear();
            file.seekg(0);
        }

        while (std::getline(file, line)) {
            if (trim(line).empty()) continue;
            std::istringstream ss(line);
            std::string token;

            std::string accountNumber, accountType, iban, branchCode, holderName, openingDateStr, status, balanceStr, customerId;

            std::getline(ss, accountNumber, ',');
            std::getline(ss, accountType, ',');
            std::getline(ss, iban, ',');
            std::getline(ss, branchCode, ',');
            std::getline(ss, holderName, ',');
            std::getline(ss, openingDateStr, ',');
            std::getline(ss, status, ',');
            std::getline(ss, balanceStr, ',');
            std::getline(ss, customerId, ',');

            accountNumber = trim(accountNumber);
            accountType = trim(accountType);
            iban = trim(iban);
            branchCode = trim(branchCode);
            holderName = trim(holderName);
            openingDateStr = trim(openingDateStr);
            status = trim(status);
            balanceStr = trim(balanceStr);
            customerId = trim(customerId);

            Date::Date openingDate = Date::FromString(openingDateStr);
            double balance = 0.0;
            try { balance = std::stod(balanceStr); } catch(...) { balance = 0.0; }

            accounts[count] = Account::Create(holderName, accountType, branchCode, status, customerId, accountNumber, openingDate, balance);
            ++count;

            // link to customer if provided
            if (customers != nullptr && customerCountPtr != nullptr) {
                for (int i = 0; i < *customerCountPtr; ++i) {
                    if (customers[i].Id == customerId) {
                        Customer::AddAccount(&customers[i], accounts[count - 1]);
                        break;
                    }
                }
            }
            if (count >= 10000) break; // safety
        }

        file.close();
    }

    // Write accounts array to CSV (overwrite)
    inline void Write(
        Account::Account accounts[],
        int count,
        const std::string& filename = "accounts.csv"
    ) {
        std::ofstream file(GetFilePath() + filename, std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "Unable to open accounts file for writing\n";
            return;
        }

        // Header
        file << "AccountNumber,AccountType,IBAN,BranchCode,HolderName,OpeningDate,Status,Balance,CustomerId\n";
        for (int i = 0; i < count; ++i) {
            const auto& A = accounts[i];
            file << A.AccountNumber << ","
                    << A.AccountType << ","
                    << A.IBAN << ","
                    << A.BranchCode << ","
                    << A.HolderName << ","
                    << Date::ToString(A.OpeningDate) << ","
                    << A.Status << ","
                    << A.Balance << ","
                    << A.CustomerId << "\n";
        }

        file.close();
    }

} // namespace AccountCSV

#endif
