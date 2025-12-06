#ifndef CPPTOJSON_H
#define CPPTOJSON_H
#include "json.hpp"
#include "../../../../BackEnd/Include/Models/Account.h"
#include "../../../../BackEnd/Include/Models/Employee.h"
#include "../../../../BackEnd/Include/DataStructures/Stack.h"

using json = nlohmann::json;
using namespace std ;

string StringifyAccount(const string& AccNum);
string StringifyAllAccounts();
string StringifyAllLoans(const Doubly::List<Loan::Loan> & L );
string StringifyLoan(const Loan::Loan&L);
string StringifyAllTransactions(const Stack::Stack<Transaction::Transaction> & trans);
string StringifyTransaction(Transaction::Transaction& T);


string StringifyEmployee(const Employee::Employee&Emp);
string StringifyAllEmployees();



#endif