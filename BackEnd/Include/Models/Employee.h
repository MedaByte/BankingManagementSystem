#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Date.h"

struct Employee {
	int Id;
	std::string Name;
	std::string LastName;
	std::string Address;
	double Salary;
	Date::Date HireDate;
	std::string BranchCode;
};

#endif
