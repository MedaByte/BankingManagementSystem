#ifndef ACCOUNT_CSV_H
#define ACCOUNT_CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/Models/Account.h"
#include "../Include/DataStructures/SinglyLinkedList.h"
#include "../Include/Utils/OriginPath.h"

namespace AccountCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/accounts.csv";
    }

    inline void WriteHeader(std::ofstream& File) {
        File << "AccountNumber,CustomerId,HolderName,AccountType,IBAN,BranchCode,"
                << "OpeningDate,Status,Balance\n";
    }

    inline bool FileIsEmpty(const std::string& path) {
        std::ifstream f(path);
        return f.peek() == std::ifstream::traits_type::eof();
    }

    inline void Write(const Account::Account& A) {
        std::string path = GetFilePath();
        std::ofstream File(path, std::ios::app);

        if (!File.is_open()) {
            std::cerr << "Cannot open accounts.csv\n";
            return;
        }

        // Write header only once
        if (FileIsEmpty(path)) {
            WriteHeader(File);
        }

        File << A.AccountNumber << ","
                << A.CustomerId << ","
                << A.HolderName << ","
                << A.AccountType << ","
                << A.IBAN << ","
                << A.BranchCode << ","
                << A.OpeningDate.Day << "/"
                << A.OpeningDate.Month << "/"
                << A.OpeningDate.Year << ","
                << A.Status << ","
                << A.Balance << "\n";
    }

    inline Singly::List<Account::Account> ReadAll() {
        Singly::List<Account::Account> List = Singly::Create<Account::Account>();

        std::ifstream File(GetFilePath());
        if (!File.is_open()) return List;

        std::string Line;
        std::getline(File, Line); // skip header

        while (std::getline(File, Line)) {
            if (Line.empty()) continue;

            std::stringstream ss(Line);
            std::string accNum, customerId, holder, type, iban, branch, date, status, balance;

            std::getline(ss, accNum, ',');
            std::getline(ss, customerId, ',');
            std::getline(ss, holder, ',');
            std::getline(ss, type, ',');
            std::getline(ss, iban, ',');
            std::getline(ss, branch, ',');
            std::getline(ss, date, ',');
            std::getline(ss, status, ',');
            std::getline(ss, balance, ',');

            int d = 1, m = 1, y = 2000;
            sscanf(date.c_str(), "%d/%d/%d", &d, &m, &y);

            double bal = 0.0;
            try { if (!balance.empty()) bal = std::stod(balance); } catch(...) { bal = 0.0; }

            Account::Account A{
                accNum, type, iban, branch, holder,
                {d, m, y}, status, bal, customerId,
                Doubly::Create<Loan::Loan>(),
                Stack::Create<Transaction::Transaction>()
            };

            Singly::PushBack(&List, A);
        }

        return List;
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }
}

#endif
