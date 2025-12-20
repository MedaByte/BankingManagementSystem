#ifndef CSVINITIALIZER_H
#define CSVINITIALIZER_H

#include "OriginPath.h"
#include <fstream>
#include <iostream>
#include <string>

// We won't be needing that because plans changed | Não vamos precisar disso porque os planos mudaram

namespace Utils
{

    // Check if a file exists | Verifica se um arquivo existe
    inline bool FileExists(const std::string &path)
    {
        std::ifstream f(path);
        return f.good();
    }

    // Create a file with header if it does not exist | Cria um arquivo com cabeçalho se não existir
    inline void CreateFileIfMissing(const std::string &path, const std::string &header)
    {
        std::ofstream file(path, std::ios::trunc);
        if (file.is_open())
        {
            file << header;
            file.close();
            std::cout << "Created -> " << path << "\n";
        }
        else
        {
            std::cerr << "Error upon Creation: " << path << "\n";
        }
    }

    // Initialize all necessary CSV files | Inicializa todos os arquivos CSV necessários
    inline void InitializeCSVFiles()
    {
        const std::string dataFolder = Utils::GetOriginFolder() + "/BackEnd/Data/";

        CreateFileIfMissing(
            dataFolder + "loans.csv",
            "LoanID,Amount,InterestRate,StartDay/StartMonth/StartYear,EndDay/EndMonth/EndYear,Status\n");

        CreateFileIfMissing(
            dataFolder + "transactions.csv",
            "TransactionID,AccountNumber,Type,Amount,Day/Month/Year\n");

        CreateFileIfMissing(
            dataFolder + "accounts.csv",
            "AccountNumber,HolderName,AccountType,IBAN,BranchCode,OpeningDate,Status,Balance\n");

        CreateFileIfMissing(
            dataFolder + "customers.csv",
            "CustomerID,Name,LastName,Address,Phone\n");

        CreateFileIfMissing(
            dataFolder + "employees.csv",
            "Id,Name,LastName,Address,Salary,HireDay/HireMonth/HireYear,BranchCode,Status\n");

        std::cout << "CSVs r goodtogo\n"; // CSVs are ready | CSVs estão prontos
    }

}

#endif
