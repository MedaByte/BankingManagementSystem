#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include "../Utils/IdGenerator.h"
#include "../Utils/OriginPath.h"
#include "Account.h"
#include "../DataStructures/SinglyLinkedList.h"

namespace Customer {

    struct Customer {
        std::string Id;        // Customer ID | ID do customer
        std::string Name;      // First name | Primeiro nome
        std::string LastName;  // Last name | Último nome
        std::string Address;   // Address | Endereço
        std::string Phone;     // Phone | Telefone

        Singly::List<Account::Account> Accounts; // List of accounts | Lista de accounts
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
            Singly::Create<Account::Account>()  // Init accounts list | Inicializar lista de accounts
        };

        return NewCustomer; // Return new customer | Retornar novo customer
    }

    inline void AddAccount(Customer* C, const Account::Account& A) {
        Singly::PushBack(&C->Accounts, A);
        // Add account | Adicionar account
    }

    inline Account::Account* FindAccount(Customer* C, const std::string& AccountNumber) {
        auto Node = Singly::Find(
            C->Accounts,
            [&](const Account::Account& A) { return A.AccountNumber == AccountNumber; }
        );

        if (Node) return &Node->Data; // Found | Encontrado
        return nullptr;               // Not found | Não encontrado
    }

    inline void Display(const Customer& C) {
        std::cout << "Customer ID: " << C.Id << "\n";
        std::cout << "Name: " << C.Name << " " << C.LastName << "\n";
        std::cout << "Address: " << C.Address << "\n";
        std::cout << "Phone: " << C.Phone << "\n";
        std::cout << "Accounts: " << C.Accounts.Size << "\n";
        // Display customer info | Mostrar informações do customer
    }

}

#endif
