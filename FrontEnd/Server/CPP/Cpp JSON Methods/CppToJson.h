#ifndef CPPTOJSON_H
#define CPPTOJSON_H
#include "json.hpp"
#include "../../../../BackEnd/Include/Models/Account.h"
#include "../../../../BackEnd/Include/Models/Employee.h"
#include "../../../../BackEnd/Include/Models/Customer.h"
#include "../../../../BackEnd/Include/Models/Loan.h"
#include "../../../../BackEnd/Include/Models/Transaction.h"
#include "../../../../BackEnd/Include/DataStructures/Stack.h"

#include "../../../../BackEnd/Include/Models/Date.h"
#include "../../../../BackEnd/Include/Utils/MergeSort.h"
#include "../../../../BackEnd/Include/Controllers/AccountController.h"
#include "../../../../BackEnd/Include/Controllers/EmployeeController.h"
#include "../../../../BackEnd/CSV/AccountCSV.h"
#include "../../../../BackEnd/CSV/TransactionCSV.h"
#include "../../../../BackEnd/CSV/EmployeeCSV.h"
#include "../../../../BackEnd/CSV/CustomerCSV.h"
#include "../../../../BackEnd/CSV/CompletedLoans.h"

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
using namespace std;

string StringifyAccount(const string &AccNum);
string StringifyAllAccounts();
string StringifyAllLoans(const Doubly::List<Loan::Loan> &L);
string StringifyLoan(const Loan::Loan &L);
string StringifyAllTransactions(const Stack::Stack<Transaction::Transaction> &trans);
string StringifyTransaction(const Transaction::Transaction &T);

void loadEverything();
string StringifyEmployee(const string &EmpId);
string StringifyAllEmployees();
string StringifyAllCustomersNumbers(); // ["CUS0001","CUS0002"...]



string StringifyLoanStatistics(int TL , int B , int C , int H , int S , int G , int A , int CMP , int O , int R);
string StringifyCustomerStatistics(int a1 ,string a2 , string a3 ,string a4 , string a5 , string a6 , string a7 , string a8 ,string a9,string a10);
string StringifyEmployeeStatistics(int,string,string,string,string,string,string);

#endif