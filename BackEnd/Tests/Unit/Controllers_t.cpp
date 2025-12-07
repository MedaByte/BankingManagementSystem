#include <iostream>
#include <string>
#include "../Include/Models/Customer.h"
#include "../Include/Models/Account.h"
#include "../Include/Models/Employee.h"
#include "../Include/Models/Loan.h"
#include "../Include/Models/Transaction.h"
#include "../Include/Models/Date.h"
#include "../Include/Controllers/AccountController.h"
#include "../Include/Controllers/CustomerController.h"
#include "../Include/Controllers/EmployeeController.h"
#include "../Include/Controllers/LoanController.h"
#include "../CSV/CustomerCSV.h"
#include "../CSV/AccountCSV.h"
#include "../CSV/EmployeeCSV.h"
#include "../CSV/LoanCSV.h"
#include "../CSV/TransactionCSV.h"

/*int main() {
    std::cout << "=== Ultimate Banking System Test ===\n\n";

    // === Clear all data first ===
    CustomerCSV::Clear();
    AccountCSV::Clear();
    EmployeeCSV::Clear();
    LoanCSV::Clear();
    TransactionCSV::Clear();
    std::cout << "CSV files cleared.\n";

    // === Create Customers ===
    auto customer1 = Customer::Create("Alice", "Wonder", "123 Fantasy St", "11111111");
    auto customer2 = Customer::Create("Bob", "Builder", "456 Construction Rd", "22222222");
    CustomerController::Create(customer1);
    CustomerController::Create(customer2);
    std::cout << "Customers created.\n";

    // === Create Accounts ===
    auto acc1 = Account::Create("Alice Wonder", "Savings", "01", "Active", customer1.Id);
    auto acc2 = Account::Create("Alice Wonder", "Checking", "01", "Active", customer1.Id);
    auto acc3 = Account::Create("Bob Builder", "Savings", "02", "Active", customer2.Id);
    AccountController::Create(acc1);
    AccountController::Create(acc2);
    AccountController::Create(acc3);
    CustomerController::AddAccount(&customer1, acc1);
    CustomerController::AddAccount(&customer1, acc2);
    CustomerController::AddAccount(&customer2, acc3);
    std::cout << "Accounts created and assigned to customers.\n";

    // === Create Employees ===
    auto emp1 = Employee::Create("Charlie", "Manager", "789 Admin Ln", 3000, "01");
    EmployeeController::Create(emp1);
    EmployeeController::ChangeSalary(&emp1, 3500);
    EmployeeController::ChangeStatus(&emp1, "Inactive");
    std::cout << "Employee created and updated.\n";

    // === Create Loans ===
    Loan::Loan loan1{"LOAN001", acc1.AccountNumber, 5000, 0.05, 0, 5000, Date::Now(), Date::Now(), "Active", Stack::Create<Transaction::Transaction>()};
    Loan::Loan loan2{"LOAN002", acc3.AccountNumber, 10000, 0.07, 0, 10000, Date::Now(), Date::Now(), "Active", Stack::Create<Transaction::Transaction>()};
    LoanController::Create(loan1);
    LoanController::Create(loan2);
    Account::AddLoan(&acc1, loan1);
    Account::AddLoan(&acc3, loan2);
    std::cout << "Loans created and added to accounts.\n";

    // === Transactions ===
    TransactionController::DoTransaction(acc1.AccountNumber, "DEPOSIT", 1000);
    TransactionController::DoTransaction(acc1.AccountNumber, "WITHDRAW", 300);
    TransactionController::DoTransaction(acc3.AccountNumber, "DEPOSIT", 2000);
    TransactionController::DoTransaction(acc3.AccountNumber, "WITHDRAW", 500);
    std::cout << "Transactions performed.\n";

    // === Undo last transaction ===
    Account::UndoLastTransaction(&acc3);
    std::cout << "Undo last transaction for acc3.\n";

    // === Find and update account ===
    Account::ChangeStatus(&acc2, "Inactive");
    AccountController::Update(acc2);
    std::cout << "Account2 status changed to Inactive and saved.\n";

    // === Read all CSVs and display ===
    auto allCustomers = CustomerCSV::ReadAll();
    std::cout << "\n--- All Customers ---\n";
    for (auto cNode = allCustomers.Head; cNode; cNode = cNode->Next) Customer::Display(cNode->Data);

    auto allAccounts = AccountCSV::ReadAll();
    std::cout << "\n--- All Accounts ---\n";
    for (auto aNode = allAccounts.Head; aNode; aNode = aNode->Next) Account::Display(aNode->Data);

    auto allLoans = LoanCSV::ReadAll();
    std::cout << "\n--- All Loans ---\n";
    for (auto lNode = allLoans.Head; lNode; lNode = lNode->Next) std::cout << "[" << lNode->Data.Id << ", " << lNode->Data.Amount << "]\n";

    auto allTransactions = TransactionCSV::ReadAll();
    std::cout << "\n--- All Transactions ---\n";
    for (auto tNode = allTransactions.Head; tNode; tNode = tNode->Next) std::cout << "[" << tNode->Data.TransactionId << ", " << tNode->Data.Type << ", " << tNode->Data.Amount << "]\n";

    std::cout << "\n=== Test Completed Successfully ===\n";
    return 0;
}
*/