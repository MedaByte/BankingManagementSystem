#ifndef ACCOUNTCSV_H
#define ACCOUNTCSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/Models/Account.h"
#include "../Include/Models/Date.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/Models/Customer.h"

namespace AccountCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // ============================================================
    // LOAD ACCOUNTS
    // ============================================================
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

        // Detect header
        if (!std::getline(file, line)) return;
        std::istringstream peek(line);
        std::string firstTok;
        std::getline(peek, firstTok, ',');
        bool isHeader = (firstTok.find_first_not_of("0123456789") != std::string::npos);
        if (!isHeader) {
            file.clear();
            file.seekg(0);
        }

        while (std::getline(file, line)) {
            if (trim(line).empty()) continue;

            std::istringstream ss(line);

            std::string accountNumber, accountType, iban, branchCode, holderName;
            std::string openingDateStr, status, balanceStr, customerId;
            std::string noteStr, imageStr;

            std::getline(ss, accountNumber, ',');
            std::getline(ss, accountType, ',');
            std::getline(ss, iban, ',');
            std::getline(ss, branchCode, ',');
            std::getline(ss, holderName, ',');

            std::getline(ss, openingDateStr, ',');
            std::getline(ss, status, ',');
            std::getline(ss, balanceStr, ',');

            std::getline(ss, customerId, ',');
            std::getline(ss, noteStr, ',');
            std::getline(ss, imageStr, ',');

            accountNumber = trim(accountNumber);
            accountType   = trim(accountType);
            iban          = trim(iban);
            branchCode    = trim(branchCode);
            holderName    = trim(holderName);
            openingDateStr= trim(openingDateStr);
            status        = trim(status);
            balanceStr    = trim(balanceStr);
            customerId    = trim(customerId);
            noteStr       = trim(noteStr);
            imageStr      = trim(imageStr);

            Date::Date openingDate = Date::FromString(openingDateStr);

            double balance = 0.0;
            try { balance = std::stod(balanceStr); } 
            catch(...) { balance = 0.0; }

            // Create account
            accounts[count] = Account::Create(
                holderName,
                accountType,
                branchCode,
                status,
                customerId,
                noteStr,
                accountNumber,
                openingDate,
                balance,
                imageStr
            );

            // Link account to customer
            if (customers != nullptr && customerCountPtr != nullptr) {
                for (int i = 0; i < *customerCountPtr; ++i) {
                    if (customers[i].Id == customerId) {
                        Customer::AddAccount(&customers[i], accounts[count]);
                        break;
                    }
                }
            }

            count++;
            if (count >= 10000) break;
        }

        file.close();
    }

    // ============================================================
    // WRITE ACCOUNTS
    // ============================================================
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

        // Updated Header
        file << "AccountNumber,AccountType,IBAN,BranchCode,HolderName,OpeningDate,Status,Balance,CustomerId,Note,Image\n";

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
                    << A.CustomerId << ","
                    << A.Note << ","
                    << A.Image << "\n";
        }

        file.close();
    }

} // namespace AccountCSV

#endif
