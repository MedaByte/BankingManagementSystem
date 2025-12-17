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

namespace TransactionCSV
{

    // Get CSV file path | Pega o caminho do arquivo CSV
    inline std::string GetFilePath()
    {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    // Trim whitespace | Remove espaços em branco
    inline std::string trim(const std::string &s)
    {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos)
            return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load transactions from CSV and link to accounts/customers | Carrega transactions do CSV e liga a accounts/customers
    inline void Load(Transaction::Transaction transactions[], int &count,
                     Account::Account accounts[], int accountCount,
                     Customer::Customer customers[], int customerCount,
                     const std::string &filename = "transactions.csv")
    {

        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open())
            return;

        std::string line;
        count = 0;

        // Check header | Verifica header
        if (!std::getline(file, line))
            return;
        std::istringstream peek(line);
        std::string firstTok;
        std::getline(peek, firstTok, ',');
        bool isHeader = (firstTok.find_first_not_of("0123456789") != std::string::npos);
        if (!isHeader)
        {
            file.clear();
            file.seekg(0);
        }

        while (std::getline(file, line))
        {
            if (trim(line).empty())
                continue;
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
            try
            {
                amount = std::stod(amountStr);
            }
            catch (...)
            {
                amount = 0.0;
            }

            Date::Date d = Date::FromString(dateStr);

            // Create transaction object | Cria objeto transaction
            transactions[count] = Transaction::Create(accNum, type, amount, d, txId);

            // Link transaction to account's stack and update customer account | Liga transaction ao stack do account e atualiza customer
            for (int i = 0; i < accountCount; ++i)
            {
                if (accounts[i].AccountNumber == accNum)
                {
                    Stack::Push(&accounts[i].DailyTransactions, transactions[count]);
                    for (int j = 0; j < customerCount; ++j)
                    {
                        if (customers[j].Id == accounts[i].CustomerId)
                        {
                            auto accNode = customers[j].Accounts.Head;
                            while (accNode)
                            {
                                if (accNode->Data.AccountNumber == accNum)
                                {
                                    accNode->Data = accounts[i]; // Update account | Atualiza account
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
            if (count >= 100000)
                break; // Safety limit | Limite de segurança
        }

        file.close();
    }

    // Write transactions to CSV | Escreve transactions no CSV
    inline void Write(Transaction::Transaction transactions[], int count, const std::string &filename = "transactions.csv")
    {
        if (count == 0)
        {
            std::ofstream(GetFilePath() + filename);
            return;
        }
        std::ofstream file(GetFilePath() + filename, std::ofstream::trunc);
        if (!file.is_open())
        {
            std::cerr << "Unable to open transactions file for writing\n"; // Erro ao abrir arquivo
            return;
        }

        // Header | Cabeçalho
        file << "TransactionId,AccountNumber,Type,Amount,Date\n";

        const auto &T = transactions[count - 1];

        for (int i = 0; i < count - 1; ++i)
        {
            const auto &T = transactions[i];
            file << T.TransactionId << ","
                 << T.AccountNumber << ","
                 << T.Type << ","
                 << T.Amount << ","
                 << Date::ToString(T.Date) << "\n";
        }
        file << T.TransactionId << ","
             << T.AccountNumber << ","
             << T.Type << ","
             << T.Amount << ","
             << Date::ToString(T.Date) << "\n";

        file.close();
    }

} // namespace TransactionCSV

#endif
