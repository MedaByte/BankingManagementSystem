#include "CppToJson.h"

#include "../../../../BackEnd/Include/DataStructures/Stack.h"
#include "../../../../BackEnd/Include/Models/Date.h"
#include "../../../../BackEnd/Include/Utils/MergeSort.h"
#include "../../../../BackEnd/Include/Controllers/AccountController.h"
#include "../../../../BackEnd/Include/Controllers/EmployeeController.h"
#include "../../../../BackEnd/CSV/AccountCSV.h"
#include "../../../../BackEnd/CSV/TransactionCSV.h"
#include "../../../../BackEnd/CSV/EmployeeCSV.h"
#include "../../../../BackEnd/CSV/CustomerCSV.h"

using namespace std;



// ---------------------- Helper ----------------------
int indexOf(const string* arr, int size, const string& id) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == id) return i;
    }
    return -1;
}



// ---------------------- GLOBAL ARRAYS ----------------------
Customer::Customer customers[MAX_CUSTOMERS];
Employee::Employee employees[MAX_EMPLOYEES];
Account::Account accounts[MAX_ACCOUNTS];
Loan::Loan loanRequests[MAX_LOAN_REQUESTS];
Loan::Loan loans[MAX_LOANS];
Transaction::Transaction transactions[MAX_TRANSACTIONS];


// ---------------------- COUNTERS ----------------------
int customerCount = 0;
int employeeCount = 0;
int accountCount = 0;
int loanRequestCount = 0;
int loanCount = 0;
int transactionCount = 0;



// ---------------------- LOADING ----------------------
void loadEverything() {
    CustomerCSV::Load(customers, customerCount);
    AccountCSV::Load(accounts, accountCount, customers, &customerCount);
    EmployeeCSV::Load(employees, employeeCount);
    LoanCSV::Load(loans, loanCount, accounts, accountCount);
    TransactionCSV::Load(transactions, transactionCount, accounts, accountCount, customers, customerCount);
}



// ========================= ACCOUNT JSON =========================

string StringifyTransaction(const Transaction::Transaction& T) {
    string json = "{";

    json += "\"type\":\"" + T.Type + "\",";
    json += "\"amount\":" + to_string(T.Amount) + ",";
    json += "\"date\":\"" + Date::ToString(T.Date) + "\",";
    json += "\"id\":\"" + T.TransactionId + "\"";

    json += "}";
    return json;
}

string StringifyAllTransactions(const Stack::Stack<Transaction::Transaction>& trans) {
    string json = "[";
    for (auto n = trans.List.Head; n; n = n->Next) {
        json += StringifyTransaction(n->Data);
        if (n->Next) json += ",";
    }
    json += "]";
    return json;
}



string StringifyLoan(const Loan::Loan& L) {
    string json = "{";

    json += "\"type\":\"" + L.type + "\",";
    json += "\"startDate\":\"" + Date::ToString(L.StartDate) + "\",";
    json += "\"endDate\":\"" + Date::ToString(L.EndDate) + "\",";
    json += "\"amount\":\"" + to_string(L.Amount) + "\",";
    json += "\"interestRate\":\"" + to_string(L.InterestRate) + "\",";
    json += "\"id\":\"" + L.Id + "\",";
    json += "\"paidAmount\":\"" + to_string(L.PaidAmount) + "\",";
    json += "\"remainingBalance\":\"" + to_string(L.RemainingAmount) + "\",";
    json += "\"status\":\"" + L.Status + "\"";

    json += "}";
    return json;
}

string StringifyAllLoans(const Doubly::List<Loan::Loan>& L) {
    string json = "[";
    for (auto n = L.Head; n; n = n->Next) {
        json += StringifyLoan(n->Data);
        if (n->Next) json += ",";
    }
    json += "]";
    return json;
}



string StringifyAccount(const string& AccNum) {
    static string storedImgs[] = {"ACC0001", "ACC0002" , "ACC0003", "ACC0004", "ACC0005", "ACC0006", "ACC0007", "ACC0008","ACC0009","ACC0010",
                                 "ACC0011", "ACC0012", "ACC0013", "ACC0014", "ACC0015"};

    Account::Account* accPtr = AccountController::FindAccount(accounts, accountCount, AccNum);
    if (!accPtr) return "{}";

    const Account::Account& acc = *accPtr;

    string imgToLoad = (indexOf(storedImgs, 15, acc.AccountNumber) != -1)
        ? acc.AccountNumber
        : "default";

    string json = "{";

    json += "\"OpeningDate\":\"" + Date::ToString(acc.OpeningDate) + "\",";
    json += "\"customerId\":\"" + acc.CustomerId + "\",";
    json += "\"IBAN\":\"" + acc.IBAN + "\",";
    json += "\"balance\":\"" + to_string(acc.Balance) + "\",";
    json += "\"type\":\"" + acc.AccountType + "\",";
    json += "\"status\":\"" + acc.Status + "\",";
    json += "\"accountName\":\"" + acc.HolderName + "\",";
    json += "\"number\":\"" + acc.AccountNumber + "\",";
    json += "\"branch\":\"" + acc.BranchCode + "\",";
    json += "\"note\":\"" + acc.Note + "\",";
    json += "\"img\":\"" + imgToLoad + "\",";

    json += "\"transactions\":" + StringifyAllTransactions(acc.DailyTransactions) + ",";
    json += "\"Loans\":" + StringifyAllLoans(acc.Loans);

    json += "}";
    return json;
}



string StringifyAllAccounts() {
    string json = "[";
    for (int i = 0; i < accountCount; i++) {
        json += StringifyAccount(accounts[i].AccountNumber);
        if (i != accountCount - 1) json += ",";
    }
    json += "]";
    return json;
}



// ========================= EMPLOYEE JSON =========================

string StringifyEmployee(const string& EmpId) {
    static string storedImgs[] = {"EMP0001", "EMP0002", "EMP0003", "EMP0004", "EMP0005",
                                 "EMP0006", "EMP0007", "EMP0008", "EMP0009", "EMP0010","EMP0011",
                                 "EMP0012", "EMP0013", "EMP0014", "EMP0015"};

    Employee::Employee* empPtr = EmployeeController::FindEmployee(employees, employeeCount, EmpId);
    if (!empPtr) return "{}";

    const Employee::Employee& E = *empPtr;

    string imgToLoad = (indexOf(storedImgs, 15, E.Id) != -1)
        ? E.Id
        : "default";

    string json = "{";

    json += "\"HireDate\":\"" + Date::ToString(E.HireDate) + "\",";
    json += "\"EmployeeId\":\"" + E.Id + "\",";
    json += "\"Name\":\"" + E.Name + "\",";
    json += "\"LastName\":\"" + E.LastName + "\",";
    json += "\"Branch\":\"" + E.BranchCode + "\",";
    json += "\"Adress\":\"" + E.Address + "\",";
    json += "\"Salary\":\"" + to_string(E.Salary) + "\",";
    json += "\"Status\":\"" + E.Status + "\",";
    json += "\"img\":\"" + imgToLoad + "\"";

    json += "}";
    return json;
}



string StringifyAllEmployees() {
    cerr << employees[0].Name;
    Utils::MergeSort(employees, 0, employeeCount-1);
    cerr << employees[0].Name;
    string json = "[";
    for (int i = 0; i < employeeCount; i++) {
        json += StringifyEmployee(employees[i].Id);
        if (i != employeeCount - 1) json += ",";
    }
    json += "]";
    return json;
}
