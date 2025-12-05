#include <iostream>
#include "../../Include/Models/Account.h"
#include "../../Include/Models/Customer.h"
#include "../../Include/Models/Employee.h"
#include "../../Include/Models/Loan.h"
#include "../../Include/Models/Transaction.h"
#include "../../Include/Models/Date.h"

int main() {
    std::cout << "=== Testing Customer ===\n";
    Customer::Customer c = Customer::Create("Mohamed", "Mnasria", "12345678", "56037555");
    Customer::Display(c);

    std::cout << "\n=== Testing Account ===\n";
    Account::Account a = Account::Create(c.Id, "checking", "1", "active");
    Account::Display(a);

    std::cout << "\n=== Testing Employee ===\n";
    Employee::Employee e = Employee::Create("Yassine", "Ouesleti", "Boulevard St.", 400.0, "10");
    Employee::Display(e);

    std::cout << "\n=== Testing Date ===\n";
    Date::Date today = Date::Now();
    std::cout << "Today: " << Date::ToString(today) << "\n";

    std::cout << "\n=== Testing Loan ===\n";
    Loan::Loan l = Loan::Create(5000.0, 0.05, 12);
    Loan::Display(l);

    std::cout << "\n=== Testing Transaction ===\n";
    Transaction::Transaction t = Transaction::Create(a.AccountNumber, "deposit", 250.0);
    Transaction::Display(t);

    std::cout << "\n=== Adding Payment to Loan ===\n";
    Loan::AddPayment(&l, t);
    std::cout << "Last Payment in Loan:\n";
    Transaction::Transaction* last = Loan::LastPayment(&l);
    if(last) Transaction::Display(*last);

    std::cout << "\n=== Undo Payment ===\n";
    Loan::UndoLastPayment(&l);
    std::cout << "Number of payments after undo: " << l.Payments.List.Size << "\n";

    return 0;
}
