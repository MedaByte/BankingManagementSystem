#ifndef EMPLOYEECSV_H
#define EMPLOYEECSV_H

#include <fstream>
#include <sstream>
#include "../Models/Employee.h"
#include "../Models/Date.h"
#include "../Utils/OriginPath.h"

namespace EmployeeCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    inline void Load(Employee::Employee employees[], int& count, const std::string& filename = "employees.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tmp;

            Employee::Employee E;

            std::getline(ss, E.Id, ',');
            std::getline(ss, E.Name, ',');
            std::getline(ss, E.LastName, ',');
            std::getline(ss, E.Address, ',');

            std::getline(ss, tmp, ',');
            E.Salary = std::stod(tmp);

            std::getline(ss, tmp, ',');
            E.HireDate = Date::FromString(tmp);

            std::getline(ss, E.BranchCode, ',');
            std::getline(ss, E.Status, ',');

            employees[count++] = E;
        }
    }
}

#endif
