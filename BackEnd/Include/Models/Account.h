#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "../DataStructures/DoublyLinkedList.h"
#include "../DataStructures/Stack.h"
#include "Loan.h"
#include "Transaction.h"
#include "Date.h"

struct Account {
	std::string AccountNumber;
	std::string AccountType;
	std::string IBAN;
	std::string BranchCode;
	std::string HolderName;
	Date::Date OpeningDate;
	std::string Status;
	double Balance;

	Doubly::List<Loan> Loans;
	Stack::Stack<Transaction> DailyTransactions;
};

#endif
