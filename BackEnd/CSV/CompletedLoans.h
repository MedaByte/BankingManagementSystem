#ifndef COMPLETEDLOANSCSV_H
#define COMPLETEDLOANSCSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/Models/Loan.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/Models/Date.h"

namespace CompletedLoansCSV {

    // Get CSV file path | Pega o caminho do arquivo CSV
    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    // Trim whitespace | Remove espaços em branco
    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load completed loans from CSV | Carrega completed loans do CSV
    inline void Load(Loan::Loan loans[], int& count, const std::string& filename = "completed_loans.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        // Check header | Verifica header
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

            std::string id, accountId, amountStr, interestStr, paidStr,
                        remainingStr, startStr, endStr, status, typeStr;

            std::getline(ss, id, ',');
            std::getline(ss, accountId, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, interestStr, ',');
            std::getline(ss, paidStr, ',');
            std::getline(ss, remainingStr, ',');
            std::getline(ss, startStr, ',');
            std::getline(ss, endStr, ',');
            std::getline(ss, status, ',');
            std::getline(ss, typeStr, ',');

            id          = trim(id);
            accountId   = trim(accountId);
            amountStr   = trim(amountStr);
            interestStr = trim(interestStr);
            paidStr     = trim(paidStr);
            remainingStr= trim(remainingStr);
            startStr    = trim(startStr);
            endStr      = trim(endStr);
            status      = trim(status);
            typeStr     = trim(typeStr);

            double amount = 0, interest = 0, paid = 0, remaining = 0;
            try { amount = std::stod(amountStr); } catch(...) {}
            try { interest = std::stod(interestStr); } catch(...) {}
            try { paid = std::stod(paidStr); } catch(...) {}
            try { remaining = std::stod(remainingStr); } catch(...) { remaining = amount; }

            Date::Date startDate = Date::FromString(startStr);
            Date::Date endDate   = Date::FromString(endStr);

            // Create loan object | Cria objeto loan
            loans[count] = Loan::Create(
                accountId,   // AccountId
                amount,      // Amount
                interest,    // InterestRate
                0,           // DurationInMonths
                status,      // Status
                typeStr,     // Type
                id,          // Id
                startDate    // StartDate
            );

            loans[count].PaidAmount      = paid;
            loans[count].RemainingAmount = remaining;
            loans[count].EndDate         = endDate;

            ++count;
            if (count >= 100000) break; // Safety limit | Limite de segurança
        }

        file.close();
    }

    // Write completed loans to CSV | Escreve completed loans no CSV
    inline void Write(Loan::Loan loans[], int count, const std::string& filename = "completed_loans.csv") {
        std::ofstream file(GetFilePath() + filename, std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "Unable to open completed loans file for writing\n"; // Erro ao abrir arquivo
            return;
        }

        // Header | Cabeçalho
        file << "Id,AccountId,Amount,InterestRate,PaidAmount,RemainingAmount,StartDate,EndDate,Status,Type\n";

        for (int i = 0; i < count; ++i) {
            const auto& L = loans[i];
            file << L.Id << ","
                    << L.AccountId << ","
                    << L.Amount << ","
                    << L.InterestRate << ","
                    << L.PaidAmount << ","
                    << L.RemainingAmount << ","
                    << Date::ToString(L.StartDate) << ","
                    << Date::ToString(L.EndDate) << ","
                    << L.Status << ","
                    << L.type << "\n";
        }

        file.close();
    }

} // namespace CompletedLoansCSV

#endif
