#include <iostream>
#include <cassert>
#include "../Include/Controllers/AccountController.h"
#include "../Include/Controllers/CustomerController.h"
#include "../Include/Controllers/EmployeeController.h"
#include "../Include/Controllers/LoanController.h"
#include "../Include/Controllers/TransactionController.h"
#include "../Include/Utils/CSVInitializer.h"
#include "../Include/Utils/IdGenerator.h"
#include "../include/DataStructures/SinglyLinkedList.h"
#include "../include/DataStructures/DoublyLinkedList.h"
#include <assert.h>


using namespace std;

int main() {


    cout << "=== STARTING CONTROLLER TESTS ===\n";

    // ======= ACCOUNT TEST =======
    Account::Account A1{
        Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_account_id.txt", "ACC"),
        "Savings",
        "IBAN12345",
        "BR001",
        "John Doe",
        {1,1,2025},
        "Active",
        1000.0,
        Doubly::Create<Loan::Loan>(),
        Stack::Create<Transaction::Transaction>()
    };

    assert(AccountController::Create(A1) == true);

    Account::Account FoundAcc;
    assert(AccountController::FindByNumber(A1.AccountNumber, FoundAcc) == true);
    assert(FoundAcc.Balance == 1000.0);

    A1.Balance = 2000.0;
    assert(AccountController::Update(A1) == true);

    assert(AccountController::FindByNumber(A1.AccountNumber, FoundAcc) == true);
    assert(FoundAcc.Balance == 2000.0);

    cout << "AccountController tests passed!\n";

    // ======= CUSTOMER TEST =======
    Customer::Customer C1{
        Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_customer_id.txt", "CUS"),
        "Jane",
        "Doe",
        "123 Street",
        "1234567890",
        Singly::Create<Account::Account>()
    };

    assert(CustomerController::Create(C1) == true);

    Customer::Customer FoundCus;
    assert(CustomerController::FindById(C1.Id, FoundCus) == true);

    assert(CustomerController::AddAccount(&FoundCus, A1) == true);
    assert(FoundCus.Accounts.Head != nullptr);

    cout << "CustomerController tests passed!\n";

    // ======= EMPLOYEE TEST =======
    Employee::Employee E1{
        Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_employee_id.txt", "EMP"),
        "Alice",
        "Smith",
        "456 Avenue",
        3000.0,
        {5,5,2020},
        "BR001",
        "Active"
    };

    assert(EmployeeController::Create(E1) == true);
    assert(EmployeeController::ChangeSalary(&E1, 3500.0) == true);
    assert(E1.Salary == 3500.0);
    assert(EmployeeController::ChangeStatus(&E1, "Inactive") == true);
    assert(E1.Status == "Inactive");

    cout << "EmployeeController tests passed!\n";

    // ======= LOAN TEST =======
    Loan::Loan L1{
        Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_loan_id.txt", "LOAN"),
        5000.0,
        5.0,
        {1,1,2025},
        {1,1,2026},
        "Pending",
        Stack::Create<Transaction::Transaction>()
    };

    assert(LoanController::Create(L1) == true);

    auto Loans = Doubly::Create<Loan::Loan>();
    Doubly::PushBack(&Loans, L1);

    Loan::Loan* FoundLoan = LoanController::FindById(Loans, L1.Id);
    assert(FoundLoan != nullptr);

    Transaction::Transaction T1 = Transaction::Create(A1.AccountNumber, "DEPOSIT", 500.0);
    LoanController::AddPayment(FoundLoan, T1);
    assert(FoundLoan->Payments.List.Head != nullptr);

    LoanController::UndoLastPayment(FoundLoan);
    assert(FoundLoan->Payments.List.Head == nullptr);

    LoanController::ChangeStatus(FoundLoan, "Approved");
    assert(FoundLoan->Status == "Approved");

    cout << "LoanController tests passed!\n";

    // ======= TRANSACTION TEST =======
    assert(TransactionController::DoTransaction(A1.AccountNumber, "DEPOSIT", 1000.0) == true);
    assert(TransactionController::DoTransaction(A1.AccountNumber, "WITHDRAW", 500.0) == true);
    assert(TransactionController::DoTransaction("NONEXIST", "DEPOSIT", 100.0) == false);

    cout << "TransactionController tests passed!\n";

    cout << "=== ALL CONTROLLERS TESTED SUCCESSFULLY ===\n";

    return 0;
}