#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include "../Utils/IdGenerator.h"
#include "../Utils/OriginPath.h"
#include "Account.h"
#include "../DataStructures/SinglyLinkedList.h"

namespace Customer {

    struct Customer {
        std::string Id;
        std::string Name;
        std::string LastName;
        std::string Address;
        std::string Phone;

        Singly::List<Account::Account> Accounts;
    };

    inline Customer Create(
        const std::string& Name,
        const std::string& LastName,
        const std::string& Address,
        const std::string& Phone,
        std::string Id = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_customer_id.txt", "CUS")
    ) {
        Customer NewCustomer{
            Id,
            Name,
            LastName,
            Address,
            Phone,
            Singly::Create<Account::Account>()
        };

        std::ofstream outFile(Utils::GetOriginFolder() + "/BackEnd/Data/customers.csv", std::ios::app);
        if(outFile.is_open()){
            outFile << NewCustomer.Id << ","
                    << NewCustomer.Name << ","
                    << NewCustomer.LastName << ","
                    << NewCustomer.Address << ","
                    << NewCustomer.Phone << "\n";
            outFile.close();
        } else {
            std::cerr << "Error: Cannot open customers.csv to save customer.\n";
        }

        return NewCustomer;
    }
    inline void AddAccount(Customer* C, const Account::Account& A) {
        Singly::PushBack(&C->Accounts, A);
    }

    inline Account::Account* FindAccount(Customer* C, const std::string& AccountNumber) {
        auto Node = Singly::Find(C->Accounts, [&](const Account::Account& A) { return A.AccountNumber == AccountNumber; });
        if (Node) return &Node->Data;
        return nullptr;
    }

    inline void Display(const Customer& C) {
        std::cout << "Customer ID: " << C.Id << "\n";
        std::cout << "Name: " << C.Name << " " << C.LastName << "\n";
        std::cout << "Address: " << C.Address << "\n";
        std::cout << "Phone: " << C.Phone << "\n";
        std::cout << "Accounts: " << C.Accounts.Size << "\n";
    }

}

#endif