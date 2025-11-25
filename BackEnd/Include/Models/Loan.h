#ifndef LOAN_H
#define LOAN_H

#include <string>
#include "Date.h"

struct Loan {
	int LoanId;
	std::string LoanType;
	double PrincipalAmount;
	double InterestRate;
	double AmountPaid;
	double RemainingBalance;
	Date::Date StartDate;
	Date::Date EndDate;
	std::string Status;
};

#endif
