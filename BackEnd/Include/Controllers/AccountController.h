#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H

#include "../Models/Account.h"
#include "../CSV/AccountCSV.h"
#include "../Utils/OriginPath.h"
#include <string>
#include <fstream>

namespace AccountController {

    inline bool Create(const Account::Account &A){
        if(A.AccountNumber.empty() || A.HolderName.empty()) return false;
        AccountCSV::Write(A);
        return true;
    }

    inline bool FindByNumber(const std::string &AccNum, Account::Account &Result){
        auto Accounts = AccountCSV::ReadAll();
        auto Node = Singly::Find(Accounts, [&](const Account::Account &A){ return A.AccountNumber == AccNum; });
        if(Node){
            Result = Node->Data;
            return true;
        }
        return false;
    }

    inline bool Update(const Account::Account &A){
        auto Accounts = AccountCSV::ReadAll();
        bool found = false;
        AccountCSV::Clear();

        for(auto Node = Accounts.Head; Node; Node = Node->Next){
            Account::Account X = Node->Data;
            if(X.AccountNumber == A.AccountNumber){
                AccountCSV::Write(A); // customerId not changed here
                found = true;
            } else {
                AccountCSV::Write(X); // customerId remains the same
            }
        }
        return found;
    }
}

#endif
