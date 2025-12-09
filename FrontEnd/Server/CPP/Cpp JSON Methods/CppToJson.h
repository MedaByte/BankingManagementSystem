#ifndef CPPTOJSON_H
#define CPPTOJSON_H
#include "json.hpp"
#include "../../../../BackEnd/Include/Models/Account.h"
#include "../../../../BackEnd/Include/Models/Employee.h"
#include "../../../../BackEnd/Include/Models/Customer.h"
#include "../../../../BackEnd/Include/Models/Loan.h"
#include "../../../../BackEnd/Include/Models/Transaction.h"
#include "../../../../BackEnd/Include/DataStructures/Stack.h"


constexpr int MAX_CUSTOMERS = 100;
constexpr int MAX_EMPLOYEES = 50;
constexpr int MAX_ACCOUNTS = 200;
constexpr int MAX_LOAN_REQUESTS = 50;
constexpr int MAX_LOANS = 50;
constexpr int MAX_TRANSACTIONS = 5000;

// ---------------- Arrays ----------------
extern Customer::Customer customers[MAX_CUSTOMERS];
extern Employee::Employee employees[MAX_EMPLOYEES];
extern Account::Account accounts[MAX_ACCOUNTS];
extern Loan::Loan loanRequests[MAX_LOAN_REQUESTS];
extern Loan::Loan loans[MAX_LOANS];
extern Transaction::Transaction transactions[MAX_TRANSACTIONS];

// ---------------- Counters ----------------
extern int customerCount;
extern int employeeCount;
extern int accountCount;
extern int loanRequestCount;
extern int loanCount;
extern int transactionCount;

using json = nlohmann::json;
using namespace std ;

string StringifyAccount(const string& AccNum);
string StringifyAllAccounts();
string StringifyAllLoans(const Doubly::List<Loan::Loan> & L );
string StringifyLoan(const Loan::Loan&L);
string StringifyAllTransactions(const Stack::Stack<Transaction::Transaction> & trans);
string StringifyTransaction(const Transaction::Transaction& T);

void loadEverything();
string StringifyEmployee(const string& EmpId);
string StringifyAllEmployees();



#endif