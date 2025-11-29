#include <iostream>
#include "../../Include/Controllers/AccountController.h"
#include "../../Include/Controllers/CustomerController.h"
#include "../../Include/Controllers/EmployeeController.h"
#include "../../Include/Controllers/LoanController.h"
#include "../../Include/Controllers/TransactionController.h"
#include "../../Include/Utils/CSVInitializer.h"

// COLORS FOR PRETTY TEST OUTPUT
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

void PrintTest(bool cond, const std::string& name) {
    std::cout << (cond ? GREEN "[OK] " : RED "[FAIL] ") << RESET << name << "\n";
}

int main() {
    // ============================================================
    // CUSTOMER + ACCOUNT TESTS
    // ============================================================
    std::cout << "\n=== CUSTOMER + ACCOUNT CONTROLLER ===\n";

    // Create customer
    Customer::Customer C = Customer::Create("Jane", "Doe", "Street 1", "12345678");
    CustomerController::Create(C);

    // Create first account
    Account::Account A1 = Account::Create("Jane Doe", "Savings", "1", "Active", C.Id);
    CustomerController::AddAccount(&C, A1);

    // Create second account
    Account::Account A2 = Account::Create("Jane Doe", "Checking", "1", "Active", C.Id);
    CustomerController::AddAccount(&C, A2);

    // Verify in-memory accounts linked
    std::cout << "++" << C.Accounts.Size << "++";
    PrintTest(C.Accounts.Size == 2, "Customer has 2 accounts linked");

    // Verify FindById
    Customer::Customer C2;
    bool f2 = CustomerController::FindById(C.Id, C2);
    PrintTest(f2, "Find customer by ID");
    PrintTest(C2.Name == "Jane", "Customer name correct");

    std::cout << "++" << C2.Accounts.Size << "++";
    PrintTest(C2.Accounts.Size == 2, "CSV read back shows 2 accounts for customer");

    // ============================================================
    // EMPLOYEE CONTROLLER TESTS
    // ============================================================
    std::cout << "\n=== EMPLOYEE CONTROLLER ===\n";

    Employee::Employee E = Employee::Create("Bob", "Smith", "Street 2", 2000, "1");
    EmployeeController::Create(E);
    EmployeeController::ChangeSalary(&E, 2600);
    PrintTest(E.Salary == 2600, "Change employee salary");

    // ============================================================
    // LOAN CONTROLLER TESTS
    // ============================================================
    std::cout << "\n=== LOAN CONTROLLER ===\n";

    Loan::Loan L = Loan::Create(5000, 0.06, 24);
    LoanController::Create(L);
    LoanController::ChangeStatus(&L, "Approved");
    PrintTest(L.Status == "Approved", "Change loan status");

    // ============================================================
    // TRANSACTION CONTROLLER TESTS
    // ============================================================
    std::cout << "\n=== TRANSACTION CONTROLLER ===\n";

    bool dep = TransactionController::DoTransaction(A1.AccountNumber, "DEPOSIT", 1000);
    PrintTest(dep, "Deposit transaction");

    bool dep2 = TransactionController::DoTransaction(A1.AccountNumber, "WITHDRAW", 300);
    PrintTest(dep2, "Withdraw transaction");
    bool dep3 = TransactionController::DoTransaction(A1.AccountNumber, "WITHDRAW", 300);
    PrintTest(dep3, "Withdraw transaction");

    bool failWithdraw = !TransactionController::DoTransaction(A1.AccountNumber, "WITHDRAW", 999999);
    PrintTest(failWithdraw, "Withdraw fails with insufficient balance");

    Singly::Display(C.Accounts);

    // ============================================================
    // CSV READBACK TESTS
    // ============================================================
    std::cout << "\n=== CSV READBACK ===\n";

    auto accList = AccountCSV::ReadAll();
    PrintTest(accList.Size > 0, "Accounts.csv read correctly");
    Singly::Display(accList);

    auto empList = EmployeeCSV::ReadAll();
    PrintTest(empList.Size > 0, "Employees.csv read correctly");
    Singly::Display(empList);

    auto custList = CustomerCSV::ReadAll();
    PrintTest(custList.Size > 0, "Customers.csv read correctly");
    Singly::Display(custList);

    auto loanList = LoanCSV::ReadAll();
    PrintTest(loanList.Size > 0, "Loans.csv read correctly");
    Singly::Display(loanList);

    auto trxList = TransactionCSV::ReadAll();
    PrintTest(trxList.Size > 0, "Transactions.csv read correctly");
    Singly::Display(trxList);

    std::cout << "\n\n===== ALL TESTS COMPLETED =====\n";
    return 0;
}
