#include <iostream>
#include "Controllers/AccountController.h"
#include "Controllers/CustomerController.h"
#include "Controllers/EmployeeController.h"
#include "Controllers/LoanController.h"
#include "Controllers/TransactionController.h"
#include "Utils/CSVInitializer.h"

int main() {
    Utils::InitializeCSVFiles();

    // AccountController test
    Account::Account A = Account::Create("John Doe", "Savings", "1", "Active");
    AccountController::Create(A);
    
    Account::Account Result;
    if (AccountController::FindByNumber(A.AccountNumber, Result)) {
        std::cout << "Account Found: " << Result.HolderName << "\n";
    }

    // CustomerController test
    Customer::Customer C = Customer::Create("Jane", "Doe", "Street 1", "12345678");
    CustomerController::Create(C);
    Customer::Customer CR;
    if (CustomerController::FindById(C.Id, CR)) {
        std::cout << "Customer Found: " << CR.Name << "\n";
    }

    // EmployeeController test
    Employee::Employee E = Employee::Create("Bob", "Smith", "Street 2", 2000, "1");
    EmployeeController::Create(E);
    EmployeeController::ChangeSalary(&E, 2500);
    std::cout << "Employee New Salary: " << E.Salary << "\n";

    // LoanController test
    Loan::Loan L = Loan::Create(1000, 0.05, 12);
    LoanController::Create(L);
    LoanController::ChangeStatus(&L, "Paid");
    std::cout << "Loan Status: " << L.Status << "\n";

    // TransactionController test
    TransactionController::DoTransaction(A.AccountNumber, "DEPOSIT", 500);
    TransactionController::DoTransaction(A.AccountNumber, "WITHDRAW", 200);

    return 0;
}
