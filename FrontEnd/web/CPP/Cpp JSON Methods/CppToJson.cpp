#include "CppToJson.h"
#include "../../../../BackEnd/Include/DataStructures/Stack.h"
#include "../../../../BackEnd/Include/Models/Date.h"
#include "../../../../BackEnd/Include/Controllers/AccountController.h"
#include "../../../../BackEnd/Include/Controllers/EmployeeController.h"
#include "../../../../BackEnd/CSV/AccountCSV.h"
#include "../../../../BackEnd/CSV/TransactionCSV.h"
#include "../../../../BackEnd/CSV/EmployeeCSV.h"
#include "../../../../BackEnd/CSV/CustomerCSV.h"
#include "CppToJson.h"
using namespace std ;


int indexOf(string*arr,int size,string id){
  int pos = -1 ;
  for (int i = 0 ; i < size ; i++){
    if (arr[i] == id){
      pos = i ;
      return pos ;
    } 
  }
  return pos ;
}

const int MAX_CUSTOMERS = 100;
const int MAX_EMPLOYEES = 50;
const int MAX_ACCOUNTS = 200;
const int MAX_LOAN_REQUESTS = 50;
const int MAX_LOANS = 50;
const int MAX_TRANSACTIONS = 5000;

// ---------------- Arrays ----------------
Customer::Customer customers[MAX_CUSTOMERS];
Employee::Employee employees[MAX_EMPLOYEES];
Account::Account accounts[MAX_ACCOUNTS];
Loan::Loan loanRequests[MAX_LOAN_REQUESTS];
Loan::Loan loans[MAX_LOANS];
Transaction::Transaction transactions[MAX_TRANSACTIONS];

// ---------------- Counters ----------------
int customerCount = 0;
int employeeCount = 0;
int accountCount = 0;
int loanRequestCount = 0;
int loanCount = 0;
int transactionCount = 0;

void loadEverything(){
    CustomerCSV::Load(customers, customerCount);
    AccountCSV::Load(accounts, accountCount, customers, &customerCount);
    EmployeeCSV::Load(employees, employeeCount);
    LoanCSV::Load(loans, loanCount, accounts, accountCount);
    TransactionCSV::Load(transactions, transactionCount, accounts, accountCount, customers, customerCount);
    
}
// =================== ACCOUNT CPPTOJSON ==========================
string StringifyAccount(const string& AccNum){
    string StoredImages[2] = {"Acc0001", "Acc0002"}; // change when u add more images !!!!!!!!!


    loadEverything();
    Account::Account acc = *AccountController::FindAccount(accounts, accountCount, AccNum);
    
    string message = "{";
    

    message += "\"OpeningDate\":\""+ Date::ToString(acc.OpeningDate) + "\",";
    message += "\"customerId\":\""+ acc.CustomerId + "\",";
    message += "\"IBAN\":\""+ acc.IBAN + "\",";
    message += "\"balance\":\""+ to_string(acc.Balance) + "\",";
    message += "\"type\":\""+ acc.AccountType + "\",";
    message += "\"status\":\""+ acc.Status + "\","; // not same as Active , active
    message += "\"accountName\":\""+ acc.HolderName + "\",";
    message += "\"number\":\""+ acc.AccountNumber + "\",";
    message += "\"branch\":\""+ acc.BranchCode + "\",";
    message += "\"note\":\""+ acc.Note + "\",";
    string imgToLoad =  (indexOf(StoredImages,sizeof(StoredImages)/sizeof(StoredImages[0]),acc.AccountNumber) > -1 ? acc.AccountNumber:"default");
    message += "\"img\":\""+ imgToLoad + "\",";
    message += "\"transactions\":"+ StringifyAllTransactions(acc.DailyTransactions) + ","; 
    message += "\"Loans\":"+ StringifyAllLoans(acc.Loans)+"}";


    return message ;
    
    
} 


string StringifyTransaction(Transaction::Transaction& T) {
    string message = "{";
    message += "\"type\":\"" + T.Type + "\",";
    message += "\"amount\":" + to_string(T.Amount) + ",";
    
    
    message += "\"date\":\"" + Date::ToString(T.Date)+ "\",";
    message += "\"id\":\"" + T.TransactionId + "\"";
    message += "}";
    
    return message ; 
}

string StringifyAllTransactions(const Stack::Stack<Transaction::Transaction> & trans){
  string message = "[";
  for (auto curr = trans.List.Head; curr; curr = curr->Next){ 
    message += StringifyTransaction(curr->Data) + ((curr->Next != nullptr) ? "," : "");
  }
  message += "]";
  return message;
  
}




string StringifyLoan(const Loan::Loan&L) {  
  string message = "{";
  
  message += "\"type\":\""+ L.type + "\",";
  message += "\"startDate\":\""+  Date::ToString(L.StartDate) + "\",";
  message += "\"endDate\":\""+  Date::ToString(L.EndDate) + "\",";
  message += "\"amount\":\""+ to_string(L.Amount) + "\",";
  message += "\"interestRate\":\""+ to_string(L.InterestRate) + "\",";
  message += "\"id\":\""+ L.Id + "\","; 
  message += "\"paidAmount\":\""+ to_string(L.PaidAmount) + "\",";
  message += "\"remainingBalance\":\""+ to_string(L.RemainingAmount) + "\",";
  message += "\"status\":\""+ L.Status + "\"}"; // Rejected case !
  
  return message ;
}

string StringifyAllLoans(const Doubly::List<Loan::Loan>& L){
  string message = "[";
  for (auto curr = L.Head; curr; curr=curr->Next){
    message += StringifyLoan(curr->Data) + ((curr->Next != nullptr) ? "," : "");
  }
  message += "]";

  return message;
}



string StringifyAllAccounts(){
  loadEverything();
  string message = "[";


  for (int i = 0; i < accountCount; ++i){
    message += StringifyAccount(accounts[i].AccountNumber) + ((i == accountCount - 1) ? "" : ",");
  }

  message += "]";

  return message;
}

// =================== Employee CPPTOJSON ==========================

string StringifyEmployee(const Employee::Employee&Emp){
  string message = "{";
  
  message += "\"HireDate\":\""+ Date::ToString(Emp.HireDate) + "\",";
  message += "\"EmployeeId\":\""+ Emp.Id + "\",";
  message += "\"Name\":\""+ Emp.Name + "\",";
  message += "\"LastName\":\""+ Emp.LastName + "\",";
  message += "\"Branch\":\""+ Emp.BranchCode + "\",";
  message += "\"Adress\":\""+ Emp.Address + "\",";
  message += "\"Salary\":\""+ to_string(Emp.Salary)+ "TDN\",";
  message += "\"Status\":\""+ Emp.Status + "\"}"; // warning

  return message ;
}


string StringifyAllEmployees(){
  Employee::Employee Emp[MAX_EMPLOYEES];
  int EmployeeCount = 0;

  string message = "[";
  EmployeeCSV::Load(Emp, EmployeeCount);

  for (int i = 0; i < EmployeeCount; ++i){
    message += StringifyEmployee(Emp[i]) + ((i == EmployeeCount - 1) ? "" : ",");
  }

  message += "]";

  return message;
}




/*
    EMPLOYEE SAMPLE JSONS
      {
        'HireDate':'12/01/2025',
        'EmployeeId':'EMP0001',
        'Name':'Mahdi',
        'LastName':'Turki'
        ,'Branch':'0012',
        'Adress':'T/A',
        'Salary':'25 000TDN',
        'Status':'Active'
      }
*/

/*
    ACCOUNT SAMPLE JSON
{
  "OpeningDate":"12/01/2025",
  "customerId":"CUS0001",
  "IBAN":"1234 5678 9012 3456 7810",
  "balance":"150 000TND",
  "branch":1113,
  "type":"Buisness Account",
  "status":"Active",
  "accountName":"Mahdi_dev",
  "number":"ACC0001",

  "transactions": [
    {"type":"Withdraw","amount":2500,"date":"12/01/2025","id":"t207"},
    {"type":"Withdraw","amount":500,"date":"08/11/2025","id":"t217"},
    {"type":"Deposit","amount":5000,"date":"12/02/2025","id":"t200"}
  ],

  "Loans": [
    {"type":"Buisness","startDate":"12/02/2025","endDate":"12/01/2030","amount":"20 000TDN","interestRate":"2.5%","id":"L907","paidAmount":"12 000TDN","remainingBalance":"8 000TDN","status":"Completed"},
    {"type":"Request-Buisness","startDate":"12/02/2025","endDate":"12/01/2030","amount":"20 000TDN",
    "interestRate":"2.5%","id":"R987","paidAmount":"12 000TDN","remainingBalance":"8 000TDN","status":"Rejected"},
    
    {"type":"Student","startDate":"12/02/2026","endDate":"02/10/2032","amount":"30 000TDN","interestRate":"2.5%","id":"L917","paidAmount":"12 000TDN","remainingBalance":"18 000TDN","status":"Overdue"},
    {"type":"Request-Student","startDate":"10/10/2024","endDate":"02/11/2028","amount":"55 000TDN","interestRate":"2.5%","id":"R977","paidAmount":"","remainingBalance":"","status":""}
  ]
}

*/