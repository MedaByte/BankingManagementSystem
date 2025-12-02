#ifndef TRANSACTIONCSV_H
#define TRANSACTIONCSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/DataStructures/Stack.h"
#include "../Include/Models/Transaction.h"
#include "../Include/Models/Account.h"
#include "../Include/Utils/OriginPath.h"

namespace TransactionCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load transactions; optionally link to accounts array (push on DailyTransactions)
    inline void Load(Transaction::Transaction transactions[], int& count,
                    Account::Account accounts[], int accountCount,
                    Customer::Customer customers[], int customerCount,
                    const std::string& filename = "transactions.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

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

            std::string txId, accNum, type, amountStr, dateStr;
            std::getline(ss, txId, ',');
            std::getline(ss, accNum, ',');
            std::getline(ss, type, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, dateStr, ',');

            txId = trim(txId);
            accNum = trim(accNum);
            type = trim(type);
            amountStr = trim(amountStr);
            dateStr = trim(dateStr);

            double amount = 0.0;
            try { amount = std::stod(amountStr); } catch(...) { amount = 0.0; }

            Date::Date d = Date::FromString(dateStr);

            transactions[count] = Transaction::Create(accNum, type, amount, d, txId);

            // link to account if provided
            for (int i = 0; i < accountCount; ++i) {
                if (accounts[i].AccountNumber == accNum) {
                    Stack::Push(&accounts[i].DailyTransactions, transactions[count]);
                    for (int j = 0; j<customerCount; ++j){
                        if (customers[j].Id == accounts[i].CustomerId){
                            auto accNode = customers[j].Accounts.Head;
                            while (accNode) {
                                if (accNode->Data.AccountNumber == accNum) {
                                    // Replace account with updated one
                                    accNode->Data = accounts[i];

                                    break;
                                }
                                accNode = accNode->Next;
                            }
                            break;
                        }
                    }
                }
            }


            ++count;
            if (count >= 100000) break;
        }

        file.close();
    }

    inline void Write(Transaction::Transaction transactions[], int count, const std::string& filename = "transactions.csv") {
        std::ofstream file(GetFilePath() + filename, std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "Unable to open transactions file for writing\n";
            return;
        }

        file << "TransactionId,AccountNumber,Type,Amount,Date\n";
        for (int i = 0; i < count; ++i) {
            const auto& T = transactions[i];
            file << T.TransactionId << ","
                    << T.AccountNumber << ","
                    << T.Type << ","
                    << T.Amount << ","
                    << Date::ToString(T.Date) << "\n";
        }

        file.close();
    }

} // namespace TransactionCSV

#endif
