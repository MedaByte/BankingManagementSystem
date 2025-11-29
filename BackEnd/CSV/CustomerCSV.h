#ifndef CUSTOMER_CSV_H
#define CUSTOMER_CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include "../Include/Models/Customer.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/DataStructures/SinglyLinkedList.h"

namespace CustomerCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/customers.csv";
    }

    inline void WriteHeader() {
        std::ofstream File(GetFilePath(), std::ios::app);
        File.seekp(0, std::ios::end);
        if (File.tellp() == 0) {
            File << "Id,Name,LastName,Address,Phone\n";
        }
    }

    inline void Write(const Customer::Customer& C) {
        WriteHeader();

        std::ofstream File(GetFilePath(), std::ios::app);
        if(!File.is_open()) return;

        File << C.Id << ","
                << C.Name << ","
                << C.LastName << ","
                << C.Address << ","
                << C.Phone << "\n";
    }

    inline Singly::List<Customer::Customer> ReadAll() {
        auto list = Singly::Create<Customer::Customer>();

        std::ifstream File(GetFilePath());
        if (!File.is_open()) return list;

        std::string Line;
        std::getline(File, Line); // skip header

        while (std::getline(File, Line)) {
            std::stringstream ss(Line);

            std::string id, name, last, address, phone;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, last, ',');
            std::getline(ss, address, ',');
            std::getline(ss, phone, ',');

            Customer::Customer C{
                id, name, last, address, phone,
                Singly::Create<Account::Account>()
            };

            Singly::PushBack(&list, C);
        }

        return list;
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
    }
}

#endif
