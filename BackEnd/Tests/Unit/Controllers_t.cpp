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
    Utils::InitializeCSVFiles();

    // ============================================================
    //  ACCOUNT CONTROLLER TESTS
    // ============================================================
    std::cout << "\n=== ACCOUNT CONTROLLER ===\n";

    Account::Account A = Account::Create("John Doe", "Savings", "1", "Active");
    AccountController::Create(A);

    Account::Account A2;
    bool f1 = AccountController::FindByNumber(A.AccountNumber, A2);
    PrintTest(f1, "Find account by number");

    bool balanceCorrect = (A2.Balance == A.Balance);
    PrintTest(balanceCorrect, "Check initial balance");

    // ============================================================
    //  CUSTOMER CONTROLLER TESTS
    // ============================================================
    std::cout << "\n=== CUSTOMER CONTROLLER ===\n";

    Customer::Customer C = Customer::Create("Jane", "Doe", "Street 1", "12345678");
    CustomerController::Create(C);

    Customer::Customer C2;
    bool f2 = CustomerController::FindById(C.Id, C2);
    PrintTest(f2, "Find customer by ID");

    PrintTest(C2.Name == "Jane", "Customer name correct");

    // ============================================================
    // EMPLOYEE CONTROLLER
    // ============================================================
    std::cout << "\n=== EMPLOYEE CONTROLLER ===\n";

    Employee::Employee E = Employee::Create("Bob", "Smith", "Street 2", 2000, "1");
    EmployeeController::Create(E);

    EmployeeController::ChangeSalary(&E, 2600);
    PrintTest(E.Salary == 2600, "Change employee salary");

    // ============================================================
    // LOAN CONTROLLER
    // ============================================================
    std::cout << "\n=== LOAN CONTROLLER ===\n";

    Loan::Loan L = Loan::Create(5000, 0.06, 24);
    LoanController::Create(L);

    LoanController::ChangeStatus(&L, "Approved");
    PrintTest(L.Status == "Approved", "Change loan status");

    // ============================================================
    // TRANSACTION CONTROLLER
    // ============================================================
    std::cout << "\n=== TRANSACTION CONTROLLER ===\n";

    bool dep = TransactionController::DoTransaction(A.AccountNumber, "DEPOSIT", 1000);
    PrintTest(dep, "Deposit transaction");

    bool dep2 = TransactionController::DoTransaction(A.AccountNumber, "WITHDRAW", 300);
    PrintTest(dep2, "Withdraw transaction");

    bool failWithdraw =
        !TransactionController::DoTransaction(A.AccountNumber, "WITHDRAW", 999999);
    PrintTest(failWithdraw, "Withdraw fails with insufficient balance");

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
