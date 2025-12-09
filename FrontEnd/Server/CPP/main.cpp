#include<iostream>
#include "Cpp JSON Methods/jsonToCpp.h"
#include "Cpp JSON Methods/CppToJson.h"
#include "../../../BackEnd/Include/Controllers/EmployeeController.h"
#include "../../../BackEnd/Include/Controllers/CustomerController.h"
#include "../../../BackEnd/Include/Controllers/LoanController.h"
#include "../../../BackEnd/CSV/CustomerCSV.h"
#include "../../../BackEnd/CSV/TransactionCSV.h"
#include "../../../BackEnd/CSV/EmployeeCSV.h"

#include <typeinfo> 
using namespace std ;

int main(){
    loadEverything();
    cerr<<"                New Run             "<<endl<<endl<<endl<<endl ;
    string input;
    getline(cin, input);
    std::cerr<< "Received input:   " << input << std::endl;
    json j = json::parse(input);
    
    string command = j["command"].get<string>();
    string info = j["info"].get<string>();

    std::cerr<< "object   " << j["object"] <<endl ;


    std::cerr<< "J is good  " <<endl ;
    std::cerr<< "Command : "<< command  << std::endl;
    std::cerr<< "Info : "<< info  << std::endl;

    if(command == "Load All Accounts"){
        std::cerr<< "Loading accounts..." <<StringifyAllAccounts()<<endl ;
        std::cout<< StringifyAllAccounts()<<endl ;
    }
    else if (command == "Load All Employees"){
        std::cout<< StringifyAllEmployees()<<endl ;
    }
    else if (command == "Load Account"){
        std::cerr<< "Loading accounts..." <<StringifyAccount(info)<<endl ;
        std::cout<< StringifyAccount(info)<<endl ;
    }
    else if (command == "Load Employee"){
        
        std::cerr<< "Loading EMployes..." <<StringifyEmployee(info)<<endl ;
        std::cout<<  StringifyEmployee(info)  <<endl ;
    }
    else if (command == "createAccount"){
        int customerCountq = 0;
        int accountCountq = 0;
        Customer::Customer cusarr[50];
        Account::Account accarr[50];
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);
        EmployeeController::AddCustomerAccount(cusarr, customerCountq, accarr, accountCountq ,j["object"]["Branch"].get<string>() , j["object"]["AccountName"].get<string>() , j["object"]["CustomerId"].get<string>() ,j["object"]["note"].get<string>() , j["object"]["AccountType"].get<string>()   ) ;
    }
    else if(command == "Add New Transaction"){
        int customerCountq = 0;
        int transactionCountq = 0;
        int accountCountq = 0;
        Customer::Customer cusarr[50];
        Transaction::Transaction tansarr[50];
        Account::Account accarr[50];
        TransactionCSV::Load(tansarr, transactionCountq, accarr, accountCountq, cusarr, customerCountq);
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);
        if(j["object"]["type"] == "Withdraw"){
            CustomerController::Withdraw( stod(j["object"]["amount"].get<string>()) , j["object"]["accountNumber"].get<string>(), accounts, accountCount, transactions, transactionCount);
        }else{
            CustomerController::Deposit (stod(j["object"]["amount"].get<string>()) , j["object"]["accountNumber"].get<string>(), accounts, accountCount, transactions, transactionCount);
        }
    }
    else if (command == "Undo Last Transaction"){
        int customerCountq = 0;
        int transactionCountq = 0;
        int accountCountq = 0;
        Customer::Customer cusarr[50];
        Transaction::Transaction tansarr[50];
        Account::Account accarr[50];
        TransactionCSV::Load(tansarr, transactionCountq, accarr, accountCountq, cusarr, customerCountq);
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);
        CustomerController::UndoTransaction(j["info"].get<string>(), accounts, accountCount, transactions, transactionCount);
    }
    else if(command == "Add Loan Request"){
        
        int customerCountq = 0;
        int loanCount = 0;
        int accountCountq = 0;
        Account::Account accarr[50];
        Customer::Customer cusarr[50];
        Loan::Loan loansarr[50];
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);
        LoanCSV::Load(loansarr, loanCount);
        std::cerr << accarr[0].AccountNumber;
        std::cerr << cusarr[0].Id;
        
        std::cerr << loansarr[10].Id;
        std::cerr << loanCount;
        
        std::cerr << "ok1";
        CustomerController::RequestLoan(loansarr, loanCount, accarr, accountCountq, j["info"].get<string>() , stod(j["object"]["amount"].get<string>()), stoi(j["object"]["duration"].get<string>()) , ("Request-"+j["object"]["type"].get<string>()) ) ;
        std::cerr << "ok2";
        std::cerr << loansarr[11].Id;
        std::cerr << loanCount;
    }
    else if (command == "Finalize Day"){
        EmployeeController::FinalizeTransactions();
    }
    else if (command == "Refuse Loan Request"){
        int customerCount = 0, loanCount = 0, loanReqCount = 0, accountCount = 0, transactionCount = 0;

        Customer::Customer cusarr[50];
        Account::Account accarr[50];
        Loan::Loan loansarr[50];
        Transaction::Transaction transarr[200];

        CustomerCSV::Load(cusarr, customerCount);
        AccountCSV::Load(accarr, accountCount, cusarr, &customerCount);
        LoanCSV::Load(loansarr, loanCount);
        TransactionCSV::Load(transarr, transactionCount, accarr, accountCount, cusarr, customerCount);

        EmployeeController::HandleSingleLoanRequest(
            j["info"].get<string>(),   
            false,                     
            cusarr, customerCount,
            accarr, accountCount,
            loansarr, loanCount,
            transarr, transactionCount
        );
    }
    else if(command == "Accept Request"){
        int customerCount = 0, loanCount = 0, loanReqCount = 0, accountCount = 0, transactionCount = 0;

        Customer::Customer cusarr[50];
        Account::Account accarr[50];
        Loan::Loan loansarr[50];
        Transaction::Transaction transarr[200];

        CustomerCSV::Load(cusarr, customerCount);
        AccountCSV::Load(accarr, accountCount, cusarr, &customerCount);
        LoanCSV::Load(loansarr, loanCount);
        TransactionCSV::Load(transarr, transactionCount, accarr, accountCount, cusarr, customerCount);

        EmployeeController::HandleSingleLoanRequest(
            j["info"].get<string>(),   
            true,                     
            cusarr, customerCount,
            accarr, accountCount,
            loansarr, loanCount,
            transarr, transactionCount
        );
    }
    else if(command == "Change Loan Status"){
        Loan::Loan loansarr[50];
        int loanCount = 0;
        LoanCSV::Load(loansarr, loanCount);
        EmployeeController::ChangeLoanStatus(loans, loanCount, j["info"].get<string>(),  j["object"]["newStatus"].get<string>()) ;

        
    }
    else if (command == "Delete Loan"){
        int customerCountq = 0;
        int loanCountq = 0;
        int accountCountq = 0;
        Account::Account accarr[50];
        Customer::Customer cusarr[50];
        Loan::Loan loansarr[50];
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);
        LoanCSV::Load(loansarr, loanCountq);
        EmployeeController::DeleteLoan(loansarr, loanCountq , j["info"].get<string>() ) ;
    }
    else if (command == "Delete Closed Accounts"){
        int customerCountq = 0;
        int accountCountq = 0;
        Account::Account accarr[50];
        Customer::Customer cusarr[50];
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);

        EmployeeController::DeleteClosedAccounts(accarr, accountCountq);
    }
    else if (command == "Delete Completed Loans"){
        int customerCountq = 0;
        int loanCountq = 0;
        int accountCountq = 0;
        Account::Account accarr[50];
        Customer::Customer cusarr[50];
        Loan::Loan loansarr[50];
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);
        LoanCSV::Load(loansarr, loanCountq);

        LoanController::DeleteCompletedLoans(loansarr, loanCountq);
    }
    else if (command == "Fire Employee"){
        int employeeCountq = 0;
        Employee::Employee emparr[50];

        EmployeeCSV::Load(emparr, employeeCountq);

        EmployeeController::DeleteEmployee(emparr, employeeCountq, j["info"].get<string>());
    }
    else if(command == "Modify Employee"){
        // employee Id : j["info"].get<string>()
        // new Salary : j["object"]["newSalary"].get<string>()
        // newBranch : j["object"]["newBranch"].get<string>()
        // newStatus : j["object"]["newStatus"].get<string>()
        cerr << "Modifying Employee..." <<endl ;

        cerr << "Employee Id: " << j["info"].get<string>() << endl ;
        cerr << "New Salary: " << j["object"]["newSalary"].get<string>()
                << " New Branch: " << j["object"]["newBranch"].get<string>()
                << " New Status: " << j["object"]["newStatus"].get<string>() << endl ;
        int employeeCountq = 0;
        Employee::Employee emparr[50];

        EmployeeCSV::Load(emparr, employeeCountq);   
        
        cerr << emparr[0].Id;
        cerr << emparr[0].BranchCode;
        EmployeeController::EditEmployee(emparr, employeeCountq, j["info"].get<string>(), stod(j["object"]["newSalary"].get<string>()), j["object"]["newBranch"].get<string>(), j["object"]["newStatus"].get<string>());
        cerr << emparr[1].Id;
        cerr << emparr[1].BranchCode;

    }
    else if (command == "Add Employee"){
        //  Employee  Name : j["object"]["EmpName"].get<string>()
        //  Employee  LastName : j["object"]["EmpLastName"].get<string>()
        //  Employee  Address : j["object"]["EmpAdress"].get<string>()
        //  Employee  Salary : j["object"]["EmpSalary"].get<string>()
        //  Employee  BranchCode : j["object"]["EmpBranch"].get<string>()
        int employeeCountq = 0;
        Employee::Employee emparr[50];

        EmployeeCSV::Load(emparr, employeeCountq);


        EmployeeController::AddEmployee(emparr, employeeCountq, j["object"]["EmpName"].get<string>(), j["object"]["EmpLastName"].get<string>(), j["object"]["EmpAdress"].get<string>(), j["object"]["EmpBranch"].get<string>(), stod(j["object"]["EmpSalary"].get<string>()));
    }
    else if (command == "Change Account Status"){
        // account number : j["info"].get<string>()
        // new status : j["object"]["newStatus"].get<string>()

        int customerCountq = 0;
        int accountCountq = 0;
        Account::Account accarr[50];
        Customer::Customer cusarr[50];
        CustomerCSV::Load(cusarr, customerCountq);
        AccountCSV::Load(accarr, accountCountq, cusarr, &customerCountq);

        EmployeeController::ChangeAccountStatus(accarr, accountCountq, j["info"].get<string>(), j["object"]["newStatus"].get<string>());
    }
    
    return 0 ;
}