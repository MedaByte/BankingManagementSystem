#ifndef TRANSACTION_CSV_H
#define TRANSACTION_CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include "../Models/Transaction.h"
#include "../DataStructures/SinglyLinkedList.h"
#include "../Utils/OriginPath.h"

namespace TransactionCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/transactions.csv";
    }

    inline void SaveTransaction(const Transaction::Transaction& T) {
        std::ofstream file(GetFilePath(), std::ios::app);
        if (!file.is_open()) return;

        file << T.TransactionId << ","
                << T.AccountNumber << ","
                << T.Type << ","
                << T.Amount << ","
                << Date::ToString(T.Date) << "\n";

        file.close();
    }

    inline Singly::List<Transaction::Transaction> LoadTransactions() {
        Singly::List<Transaction::Transaction> list = Singly::Create<Transaction::Transaction>();
        std::ifstream file(GetFilePath());
        if (!file.is_open()) return list;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, account, type, amountStr, dateStr;

            std::getline(ss, id, ',');
            std::getline(ss, account, ',');
            std::getline(ss, type, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, dateStr, ',');

            double amount = std::stod(amountStr);
            Date::Date date = Date::FromString(dateStr);

            Transaction::Transaction t{id, account, type, amount, date};
            Singly::PushBack(&list, t);
        }

        file.close();
        return list;
    }

    template <typename Predicate>
    inline Singly::List<Transaction::Transaction> FindTransactions(Predicate pred) {
        Singly::List<Transaction::Transaction> result = Singly::Create<Transaction::Transaction>();
        Singly::List<Transaction::Transaction> all = LoadTransactions();

        auto curr = all.Head;
        while (curr) {
            if (pred(curr->Data)) {
                Singly::PushBack(&result, curr->Data);
            }
            curr = curr->Next;
        }

        Singly::Clear(&all);
        return result;
    }

    inline void ClearAllTransactions() {
        std::ofstream file(GetFilePath(), std::ios::trunc);
        file.close();
    }

    inline void DisplayAll() {
        auto list = LoadTransactions();
        auto curr = list.Head;
        while (curr) {
            Transaction::Display(curr->Data);
            std::cout << "------------------------\n";
            curr = curr->Next;
        }
        Singly::Clear(&list);
    }
}

#endif
