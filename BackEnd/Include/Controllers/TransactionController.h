#ifndef TRANSACTION_CONTROLLER_H
#define TRANSACTION_CONTROLLER_H

#include <string>
#include "../Models/Transaction.h"
#include "../CSV/TransactionCSV.h"
#include "../CSV/AccountCSV.h"

namespace TransactionController {

    inline bool DoTransaction(const std::string& AccountNumber, const std::string& Type, double Amount){
        
        auto Accounts = AccountCSV::ReadAll();
        bool Found = false;

        Singly::Node<Account::Account>* Curr = Accounts.Head;

        while(Curr != nullptr){
            
            if(Curr->Data.AccountNumber == AccountNumber){
                Found = true;

                if(Type == "WITHDRAW"){
                    if(Curr->Data.Balance < Amount){
                        std::cout << "Balance ain't sufficient\n";
                        return false;
                    }
                    Curr->Data.Balance -= Amount;
                }

                else if(Type == "DEPOSIT"){
                    Curr->Data.Balance += Amount;
                }

                AccountCSV::Clear();

                auto tmp = Accounts.Head;
                while(tmp){
                    AccountCSV::Write(tmp->Data);
                    tmp = tmp->Next;
                }

                auto T = Transaction::Create(AccountNumber, Type, Amount);

                TransactionCSV::Write(T);

                std::cout << "Transaction successful!\n";
                Transaction::Display(T);

                return true;
            }

            Curr = Curr->Next;
        }  

        if(!Found){
            std::cout << "Account Ain't found\n";
        }

        return false;
    }

}

#endif
