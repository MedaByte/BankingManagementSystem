#ifndef CUSTOMER_CONTROLLER_H
#define CUSTOMER_CONTROLLER_H

#include "../Models/Customer.h"
#include "../CSV/CustomerCSV.h"
#include "../CSV/AccountCSV.h"
#include "../Utils/OriginPath.h"
#include <string>

namespace CustomerController {

    inline bool Create(const Customer::Customer &C){
        if(C.Name.empty() || C.LastName.empty()) return false;
        CustomerCSV::Write(C);
        return true;
    }

    inline bool FindById(const std::string &Id, Customer::Customer &Result){
        auto Customers = CustomerCSV::ReadAll();
        auto Node = Singly::Find(Customers, [&](const Customer::Customer &C){ return C.Id == Id; });
        if (!Node) return false;

        Result = Node->Data;

        
        auto Accounts = AccountCSV::ReadAll();
        for (auto A = Accounts.Head; A; A = A->Next) {
            if (A->Data.CustomerId == Result.Id) {
                Singly::PushBack(&Result.Accounts, A->Data);
            }
        }

        return true;
    }

    inline bool AddAccount(Customer::Customer* C, const Account::Account& A){
        Singly::PushBack(&C->Accounts, A);
        AccountController::Create(A);
        return true;
    }
}

#endif
