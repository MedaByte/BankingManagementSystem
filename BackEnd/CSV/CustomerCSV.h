#ifndef CUSTOMERCSV_H
#define CUSTOMERCSV_H

#include <fstream>
#include <sstream>
#include "../Models/Customer.h"
#include "../Utils/OriginPath.h"

namespace CustomerCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline void Load(Customer::Customer customers[], int& count, const std::string& filename = "customers.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);

            Customer::Customer C;

            std::getline(ss, C.Id, ',');
            std::getline(ss, C.Name, ',');
            std::getline(ss, C.LastName, ',');
            std::getline(ss, C.Address, ',');
            std::getline(ss, C.Phone, ',');

            C.Accounts = Singly::Create<Account::Account>();

            customers[count++] = C;
        }
    }
}

#endif
