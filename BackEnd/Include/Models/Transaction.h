#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"

struct Transaction {
	int transaction_id;
	std::string account_number;
	std::string type;
	double amount;
	Date::Date date;
};

#endif
