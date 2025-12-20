#include "CppToJson.h"



using namespace std;

// ---------------------- Helper ----------------------
int indexOf(const string *arr, int size, const string &id)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == id)
            return i;
    }
    return -1;
}

// ---------------------- GLOBAL ARRAYS ----------------------
Customer::Customer customers[MAX_CUSTOMERS];
Employee::Employee employees[MAX_EMPLOYEES];
Account::Account accounts[MAX_ACCOUNTS];
Loan::Loan completedLoans[MAX_LOAN_REQUESTS];
Loan::Loan loans[MAX_LOANS];
Transaction::Transaction transactions[MAX_TRANSACTIONS];

// ---------------------- COUNTERS ----------------------
int customerCount = 0;
int employeeCount = 0;
int accountCount = 0;
int completedLoanscount = 0;
int loanCount = 0;
int transactionCount = 0;

// ---------------------- LOADING ----------------------
void loadEverything()
{
    CustomerCSV::Load(customers, customerCount);
    AccountCSV::Load(accounts, accountCount, customers, &customerCount);
    EmployeeCSV::Load(employees, employeeCount);
    LoanCSV::Load(loans, loanCount, accounts, accountCount);
    TransactionCSV::Load(transactions, transactionCount, accounts, accountCount, customers, customerCount);
    CompletedLoansCSV::Load(completedLoans, completedLoanscount);
}

// ========================= ACCOUNT JSON =========================

string StringifyTransaction(const Transaction::Transaction &T)
{
    string json = "{";

    json += "\"type\":\"" + T.Type + "\",";
    json += "\"amount\":" + to_string(T.Amount) + ",";
    json += "\"date\":\"" + Date::ToString(T.Date) + "\",";
    json += "\"id\":\"" + T.TransactionId + "\"";

    json += "}";
    return json;
}

string StringifyAllTransactions(const Stack::Stack<Transaction::Transaction> &trans)
{
    string json = "[";
    for (auto n = trans.List.Head; n; n = n->Next)
    {
        json += StringifyTransaction(n->Data);
        if (n->Next)
            json += ",";
    }
    json += "]";
    return json;
}

string StringifyLoan(const Loan::Loan &L)
{
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

string StringifyAllLoans(const Doubly::List<Loan::Loan> &L)
{
    string json = "[";
    for (auto n = L.Head; n; n = n->Next)
    {
        json += StringifyLoan(n->Data);
        if (n->Next)
            json += ",";
    }
    json += "]";
    return json;
}

string StringifyAccount(const string &AccNum)
{
    static string storedImgs[15] = {"ACC0001", "ACC0002", "ACC0003", "ACC0004", "ACC0005", "ACC0006", "ACC0007", "ACC0008", "ACC0009", "ACC0010",
                                  "ACC0011", "ACC0012", "ACC0013", "ACC0014", "ACC0015"};

    Account::Account *accPtr = AccountController::FindAccount(accounts, accountCount, AccNum);
    if (!accPtr)
        return "{}";

    const Account::Account &acc = *accPtr;

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

string StringifyAllAccounts()
{
    string json = "[";
    for (int i = 0; i < accountCount; i++)
    {
        json += StringifyAccount(accounts[i].AccountNumber);
        if (i != accountCount - 1)
            json += ",";
    }
    json += "]";
    return json;
}

// ========================= EMPLOYEE JSON =========================

string StringifyEmployee(const string &EmpId)
{
    static string storedImgs[15] = {"EMP0001", "EMP0002", "EMP0003", "EMP0004", "EMP0005",
                                  "EMP0006", "EMP0007", "EMP0008", "EMP0009", "EMP0010", "EMP0011",
                                  "EMP0012", "EMP0013", "EMP0014", "EMP0015"};

    Employee::Employee *empPtr = EmployeeController::FindEmployee(employees, employeeCount, EmpId);
    if (!empPtr)
        return "{}";

    const Employee::Employee &E = *empPtr;

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

string StringifyAllEmployees()
{
    Utils::MergeSort(employees, 0, employeeCount - 1);
    string json = "[";
    for (int i = 0; i < employeeCount; i++)
    {
        json += StringifyEmployee(employees[i].Id);
        if (i != employeeCount - 1)
            json += ",";
    }
    json += "]";
    return json;
}

// ============== Statistics ================

string StringifyLoanStatistics(int TL , int B , int C , int H , int S , int G , int A , int CMP , int O , int R){
    string json = "[{";
    json += "\"totalNbOfLoans\":" + to_string(TL) + ",";
    json += "\"ActiveLoans\":" + to_string(A) + ",";
    json += "\"CompletedLoans\":" + to_string(CMP) + ",";
    json += "\"OverdueLoans\":" + to_string(O) + ",";
    json += "\"RequestLoans\":" + to_string(R) + ",";
    json += "\"buisnessLoans\":" + to_string(B) + ",";
    json += "\"carLoans\":" + to_string(C) + ",";
    json += "\"homeLoans\":" + to_string(H) + ",";
    json += "\"studentLoans\":" + to_string(S) + ",";
    json += "\"generalLoans\":" + to_string(G) ;
    json += "},{";

    json += "\"totalNbOfLoans\":" + Utils::percentageChange(stoi(timeLineCSV::getlastMonthLoansNumber()),TL) + ",";
    json += "\"ActiveLoans\":" + Utils::percentage(A,TL) + ",";
    json += "\"CompletedLoans\":" + Utils::percentage(CMP,TL) + ",";
    json += "\"OverdueLoans\":" + Utils::percentage(O,TL) + ",";
    json += "\"RequestLoans\":" + Utils::percentage(R,TL) + ",";
    json += "\"buisnessLoans\":" + Utils::percentage(B,TL) + ",";
    json += "\"carLoans\":" + Utils::percentage(C,TL) + ",";
    json += "\"homeLoans\":" + Utils::percentage(H,TL) + ",";
    json += "\"studentLoans\":" + Utils::percentage(S,TL) + ",";
    json += "\"generalLoans\":" + Utils::percentage(G,TL) ;
    json += "}]";

    return json ;
}

string StringifyCustomerStatistics(int a1 ,string a2 , string a3 ,string a4 , string a5 , string a6 , string a7 , string a8 ,string a9,string a10){
    string json = "{";
    json += "\"totalNbOfAccounts\":" + to_string(a1) + ",";
    json += "\"mostLoans\":{\"CusNb\":\""+ (a2) + "\",\"fullName\":\""+ (a4)+ "\",\"loanNb\":"+ (a3) + "},";
    json += "\"highestBalance\":{\"CusNb\":\""+ (a5)+"\",\"fullName\":\""+ (a7)+ "\",\"balance\":"+ (a6) + "},";
    json += "\"lowestBalance\":{\"CusNb\":\""+ (a8)+"\",\"fullName\":\""+ (a10)+ "\",\"balance\":"+ (a9) + "},";
    json+="\"percentage\":"+Utils::percentageChange(stoi(timeLineCSV::getlastMonthAccountsNumber()),a1);
    json+="}";
    return json ;


}
string StringifyEmployeeStatistics(int a1 ,string a2 , string a3 , string a4 , string a5 , string a6, string a7){
    string json = "{";
    json += "\"totalNbOfEmployees\":" + to_string(a1) + ",";
    json += "\"highestSalary\":{\"EmpNb\":\""+ (a2) + "\",\"status\":\""+ (a4)+ "\",\"salary\":"+ (a3) + "},";
    json += "\"lowestSalary\":{\"EmpNb\":\""+ (a5) + "\",\"status\":\""+ (a7)+ "\",\"salary\":"+ (a6) + "},";
    json += "\"percentage\":"+Utils::percentageChange(stoi(timeLineCSV::getlastMonthEmployeesNumber()),a1);
    json+="}";
    return json ;
}
/* EmployeesStatistics = {
          totalNbOfEmployees : 23 ,
          highestSalary : {EmpNb : "EMP0001" ,salary:2175000,status:'Active'} ,
          lowestSalary : {EmpNb : "EMP0003" ,salary:1500,status:'Vacation'},
          percentage:-8.7,

        };*/