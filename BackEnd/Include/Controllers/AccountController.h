#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H

#include "../Models/Account.h"
#include "../CSV/AccountCSV.h"
#include "../Utils/OriginPath.h"
#include <string>
#include <fstream>

namespace AccountController {

    inline bool Create(const Account::Account &A){
        if(A.AccountNumber == "" || A.HolderName == ""){
            return false;
        }

        AccountCSV::Write(A);
        return true;
    }


    inline bool FindByNumber(const std::string &AccNum, Account::Account &Result){
        std::ifstream File(Utils::GetOriginFolder() + "/BackEnd/Data/accounts.csv");

        if(!File.is_open())
            return false;

        std::string line;
        while(std::getline(File, line)){

            char AccountNumber[100];
            char HolderName[100];
            char AccountType[50];
            char IBAN[100];
            char BranchCode[50];
            char DateStr[50];
            char Status[50];
            double Balance;

            sscanf(
                line.c_str(),
                "%99[^,],%99[^,],%49[^,],%99[^,],%49[^,],%49[^,],%49[^,],%lf",
                AccountNumber,
                HolderName,
                AccountType,
                IBAN,
                BranchCode,
                DateStr,
                Status,
                &Balance
            );

            if(AccNum == AccountNumber){
                int d, m, y;
                sscanf(DateStr, "%d/%d/%d", &d, &m, &y);

                Result.AccountNumber = AccountNumber;
                Result.HolderName = HolderName;
                Result.AccountType = AccountType;
                Result.IBAN = IBAN;
                Result.BranchCode = BranchCode;
                Result.OpeningDate = {d, m, y};
                Result.Status = Status;
                Result.Balance = Balance;

                File.close();
                return true;
            }
        }

        File.close();
        return false;
    }


    inline bool Update(const Account::Account &A){

        std::ifstream Read(Utils::GetOriginFolder() + "/BackEnd/Data/accounts.csv");
        std::ofstream Temp(Utils::GetOriginFolder() + "/BackEnd/Data/accounts_temp.csv");

        if(!Read.is_open() || !Temp.is_open())
            return false;

        std::string line;
        bool found = false;

        while(std::getline(Read, line)){
            char AccountNumber[200];
            sscanf(line.c_str(), "%199[^,]", AccountNumber);

            if(A.AccountNumber == AccountNumber){
                // write updated
                Temp << A.AccountNumber << ","
                        << A.HolderName << ","
                        << A.AccountType << ","
                        << A.IBAN << ","
                        << A.BranchCode << ","
                        << A.OpeningDate.Day << "/"
                        << A.OpeningDate.Month << "/"
                        << A.OpeningDate.Year << ","
                        << A.Status << ","
                        << A.Balance << "\n";
                found = true;
            }
            else{
                Temp << line << "\n";
            }
        }

        Read.close();
        Temp.close();

        remove((Utils::GetOriginFolder() + "/BackEnd/Data/accounts.csv").c_str());
        rename(
            (Utils::GetOriginFolder() + "/BackEnd/Data/accounts_temp.csv").c_str(),
            (Utils::GetOriginFolder() + "/BackEnd/Data/accounts.csv").c_str()
        );

        return found;
    }

}

#endif
