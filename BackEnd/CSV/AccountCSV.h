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

    // Get CSV file path | Obter o caminho do arquivo CSV
    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    // Trim whitespace | Remover espaços em branco
    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load accounts from CSV | Carregar contas do CSV
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

        // Check header
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
            
            // Link to customer if provided | Vincular à conta do cliente, se fornecido
            if (customers != nullptr && customerCountPtr != nullptr) {
                for (int i = 0; i < *customerCountPtr; ++i) {
                    if (customers[i].Id == customerId) {
                        Customer::AddAccount(&customers[i], accounts[count]);
                        break;
                    }
                }
            }

            ++count;
            if (count >= 10000) break; // safety | segurança
        }

        file.close();
    }

    // Write accounts to CSV (overwrite) | Escrever contas no CSV (sobrescrever)
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

        // Header | Cabeçalho
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
