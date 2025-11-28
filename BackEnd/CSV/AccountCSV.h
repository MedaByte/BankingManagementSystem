#ifndef ACCOUNT_CSV_H
#define ACCOUNT_CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include "../Include/Models/Account.h"
#include "../Include/DataStructures/SinglyLinkedList.h"
#include "../Include/Utils/OriginPath.h"

namespace AccountCSV {

    inline std::string GetFilePath(){
        return Utils::GetOriginFolder() + "/BackEnd/Data/accounts.csv";
    }

    inline void Write(const Account::Account& A){
        std::ofstream File(GetFilePath(), std::ios::app);

        if(File.is_open()){
            File << A.AccountNumber << ","
                    << A.HolderName << ","
                    << A.AccountType << ","
                    << A.IBAN <<","
                    << A.BranchCode << ","
                    << Date::GetDay(A.OpeningDate) <<"/"
                    << Date::GetMonth(A.OpeningDate) << "/"
                    << A.OpeningDate.Year <<","
                    << A.Status <<","
                    << A.Balance <<"\n";

            File.close();
        }
    }

    inline Singly::List<Account::Account> ReadAll(){
        Singly::List<Account::Account> List = Singly::Create<Account::Account>();

        std::ifstream File(GetFilePath());
        if(!File.is_open()) return List;

        std::string Line;
        while(std::getline(File, Line)){
            std::stringstream ss(Line);
            std::string accNum, holder, type, iban, branch, date, status, balance;

            std::getline(ss, accNum, ',');
            std::getline(ss, holder, ',');
            std::getline(ss, type, ',');
            std::getline(ss, iban, ',');
            std::getline(ss, branch, ',');
            std::getline(ss, date, ',');
            std::getline(ss, status, ',');
            std::getline(ss, balance, ',');
            double bal = 0.0;
            try {
                if (!balance.empty()) {
                    bal = std::stod(balance);
                }
            } 
            catch (const std::exception& e) {
                std::cerr << "Invalid balance value '" << balance << "' in CSV. Setting to 0.\n";
                bal = 0.0;
            }

            int d, m, y;
            sscanf(date.c_str(), "%d/%d/%d", &d, &m, &y);
            Account::Account A{
                accNum,
                type,
                iban,
                branch,
                holder,
                {d, m, y},
                status,
                bal,
                Doubly::Create<Loan::Loan>(),
                Stack::Create<Transaction::Transaction>()
            };

            Singly::PushBack(&List, A);
        }

        return List;
    }

    inline void Clear(){
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }
}

#endif
