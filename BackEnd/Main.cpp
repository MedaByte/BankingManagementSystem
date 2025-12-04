#include <iostream>
#include <string>
#include "Include/Controllers/CustomerController.h"
#include "Include/Controllers/AccountController.h"
#include "Include/Controllers/LoanController.h"
#include "Include/Controllers/EmployeeController.h"
#include "Include/Controllers/StatisticsController.h"
#include "CSV/CustomerCSV.h"
#include "CSV/AccountCSV.h"
#include "CSV/EmployeeCSV.h"

#include "Include/DataStructures/Stack.h"
using namespace std;

// ---------------- Constants ----------------
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

// ---------------- Function Declarations ----------------
void CustomerMenu();
void EmployeeMenu();
void StatisticsMenu();

void WaitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------- Main ----------------
int main() {
    // ---------------- Load CSVs ----------------
    CustomerCSV::Load(customers, customerCount);
    AccountCSV::Load(accounts, accountCount, customers, &customerCount);
    EmployeeCSV::Load(employees, employeeCount);
    LoanCSV::Load(loans, loanCount, accounts, accountCount);
    TransactionCSV::Load(transactions, transactionCount, accounts, accountCount, customers, customerCount);
    
    int choice = 0;
    do {
        system("cls");

        cout << "===================== Banking Management System =====================\n";
        cout << "1. Customer Section\n";
        cout << "2. Employee Section\n";
        cout << "3. Statistics\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: CustomerMenu(); break;
            case 2: EmployeeMenu(); break;
            case 3: StatisticsMenu(); break;
            case 4: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice!\n"; WaitForEnter();
        }
    } while(choice != 4);

    return 0;
}

// ---------------- Customer Menu ----------------
void CustomerMenu() {
    string customerID;
    cout << "\n--- Customer Login ---\n";
    cout << "Enter Customer ID: ";
    cin >> customerID;
    cin.ignore();

    Customer::Customer* customer = CustomerController::FindCustomer(customers, customerCount, customerID);
    if (!customer) {
        cout << "Customer not found!\n";
        WaitForEnter();
        return;
    }

    int choice = 0;
    do {
        system("cls");
        cout << "\n--- Customer Menu (" << customer->Name << " " << customer->LastName << ") ---\n";
        cout << "1. View Accounts\n2. View Loans\n3. Request Loan\n4. Deposit Money\n5. Withdraw Money\n";
        cout << "6. View Daily Transactions\n7. Undo Last Transaction\n8. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: CustomerController::ViewAccounts(customer); WaitForEnter(); break;
            case 2: CustomerController::ViewLoans(customer); WaitForEnter(); break;
            case 3: CustomerController::RequestLoan(customer, loanRequests, loanRequestCount); WaitForEnter(); break;
            case 4: CustomerController::Deposit(customer, accounts, accountCount, transactions, transactionCount); WaitForEnter(); break;
            case 5: CustomerController::Withdraw(customer, accounts, accountCount, transactions, transactionCount); WaitForEnter(); break;
            case 6: CustomerController::ViewTransactions(customer); WaitForEnter(); break;
            case 7: CustomerController::UndoTransaction(customer, accounts, accountCount, transactions, transactionCount); WaitForEnter(); break;
            case 8: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n"; WaitForEnter();
        }
    } while(choice != 8);
}

// ---------------- Employee Menu ----------------
void EmployeeMenu() {
    string employeeID;
    cout << "\n--- Employee Login ---\n";
    cout << "Enter Employee ID: ";
    cin >> employeeID;
    cin.ignore();

    Employee::Employee* employee = nullptr;
    for (int i = 0; i < employeeCount; ++i) {
        if (employees[i].Id == employeeID) { employee = &employees[i]; break; }
    }

    if (!employee) {
        cout << "Employee not found!\n";
        WaitForEnter();
        return;
    }

    int choice = 0;
    do {
        system("cls");
        cout << "\n--- Employee Menu (" << employee->Name << " " << employee->LastName << ") ---\n";
        cout << "1. Add Employee\n2. Edit Employee\n3. Delete Employee\n4. View Employees\n";
        cout << "5. Add Customer Account\n6. View Accounts\n7. Change Account Status\n8. Delete Closed Accounts\n";
        cout << "9. View Customer Loans\n10. Change Loan Status\n11. Delete Completed Loans\n12. Manage Loan Requests\n";
        cout << "13. Finalize Daily Transactions\n14. View Earliest & Latest Employees\n15. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: EmployeeController::AddEmployee(employees, employeeCount); WaitForEnter(); break;
            case 2: EmployeeController::EditEmployee(employees, employeeCount); WaitForEnter(); break;
            case 3: EmployeeController::DeleteEmployee(employees, employeeCount); WaitForEnter(); break;
            case 4: EmployeeController::ViewEmployees(employees, employeeCount); WaitForEnter(); break;
            case 5: EmployeeController::AddCustomerAccount(customers, customerCount, accounts, accountCount); WaitForEnter(); break;
            case 6: EmployeeController::ViewAccounts(accounts, accountCount); WaitForEnter(); break;
            case 7: EmployeeController::ChangeAccountStatus(accounts, accountCount); WaitForEnter(); break;
            case 8: EmployeeController::DeleteClosedAccounts(accounts, accountCount); WaitForEnter(); break;
            case 9: EmployeeController::ViewCustomerLoans(customers, customerCount); WaitForEnter(); break;
            case 10: EmployeeController::ChangeLoanStatus(customers, customerCount, loans, loanCount); WaitForEnter(); break;
            case 11: EmployeeController::DeleteCompletedLoans(customers, customerCount, accounts, accountCount, loans, loanCount); WaitForEnter(); break;
            case 12: EmployeeController::ManageLoanRequests(customers, customerCount, loanRequests, loanRequestCount, loans, loanCount, transactions, transactionCount, accounts, accountCount); WaitForEnter(); break;
            case 13: EmployeeController::FinalizeTransactions(accounts, accountCount, transactions, transactionCount); WaitForEnter(); break;
            case 14: EmployeeController::FindEarliestAndLatestEmployees(employees, employeeCount); WaitForEnter(); break;
            case 15: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n"; WaitForEnter();
        }
    } while(choice != 15);
}

// ---------------- Statistics Menu ----------------
void StatisticsMenu() {
    int choice = 0;
    do {
        system("cls");
        cout << "\n--- Statistics Menu ---\n";
        cout << "1. Total number of loans\n2. Number of loans by type\n3. Number of loans by status\n4. Active loans in date range\n";
        cout << "5. Customer with highest number of loans\n6. Customer with highest account balance\n7. Customer with lowest account balance\n";
        cout << "8. Total number of employees\n9. Number of employees per branch\n10. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: StatisticsController::TotalLoans(customers, customerCount); WaitForEnter(); break;
            case 2: StatisticsController::LoansByType(customers, customerCount); WaitForEnter(); break;
            case 3: StatisticsController::LoansByStatus(customers, customerCount); WaitForEnter(); break;
            case 4: StatisticsController::ActiveLoansInDateRange(customers, customerCount); WaitForEnter(); break;
            case 5: StatisticsController::CustomerMostLoans(customers, customerCount); WaitForEnter(); break;
            case 6: StatisticsController::CustomerHighestBalance(customers, customerCount); WaitForEnter(); break;
            case 7: StatisticsController::CustomerLowestBalance(customers, customerCount); WaitForEnter(); break;
            case 8: StatisticsController::TotalEmployees(employees, employeeCount); WaitForEnter(); break;
            case 9: StatisticsController::EmployeesPerBranch(employees, employeeCount); WaitForEnter(); break;
            case 10: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice!\n"; WaitForEnter();
        }
    } while(choice != 10);
}
