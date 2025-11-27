#ifndef LOAN_CONTROLLER_H
#define LOAN_CONTROLLER_H
#include "../Models/Loan.h"
#include "../CSV/LoanCSV.h"
#include "../Utils/OriginPath.h"
#include <string>

namespace LoanController {
    inline bool Create(Loan::Loan &L){
        LoanCSV::Write(L);
        return true;
    }

    inline Loan::Loan* FindById(Doubly::List<Loan::Loan>& Loans, const std::string& Id){
        auto Node = Doubly::FindByID(Loans, Id);
        if(Node) return &Node->Data;
        return nullptr;
    }

    inline void AddPayment(Loan::Loan* L, const Transaction::Transaction& T){
        if(L) Loan::AddPayment(L, T);
    }

    inline void UndoLastPayment(Loan::Loan* L){
        if(L) Loan::UndoLastPayment(L);
    }

    inline void ChangeStatus(Loan::Loan* L, const std::string& NewStatus){
        if(L) Loan::ChangeStatus(L, NewStatus);
    }
}
#endif
