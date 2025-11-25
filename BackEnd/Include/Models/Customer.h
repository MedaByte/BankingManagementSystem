#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "../DataStructures/SinglyLinkedList.h"
#include "Account.h"

struct Customer {
	std::string Id;
	std::string Name;
	std::string LastName;
	std::string Address;
	std::string Phone;

	Singly::List<Account> Accounts;
};

#endif
