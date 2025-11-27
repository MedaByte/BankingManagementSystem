#ifndef CUSTOMER_CSV_H
#define CUSTOMER_CSV_H
#include <fstream>
#include <sstream>
#include <string>
#include "../Include/Models/Customer.h"
#include "../Include/DataStructures/SinglyLinkedList.h"
#include "../Include/Utils/OriginPath.h"

namespace CustomerCSV {
    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/customers.csv";
    }

    inline void Write(const Customer::Customer& C) {
        std::ofstream File(GetFilePath(), std::ios::app);
        if(File.is_open()) {
            File << C.Id << "," << C.Name << "," << C.LastName << "," << C.Address << "," << C.Phone << "\n";
            File.close();
        }
    }

    inline Singly::List<Customer::Customer> ReadAll() {
        auto List = Singly::Create<Customer::Customer>();
        std::ifstream File(GetFilePath());
        if(!File.is_open()) return List;

        std::string Line;
        while(std::getline(File, Line)) {
            std::stringstream ss(Line);
            std::string id, name, last, address, phone;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, last, ',');
            std::getline(ss, address, ',');
            std::getline(ss, phone, ',');
            Customer::Customer C{id, name, last, address, phone, Singly::Create<Account::Account>()};
            Singly::PushBack(&List, C);
        }
        return List;
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }
}
#endif
