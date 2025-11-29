#ifndef EMPLOYEE_CSV_H
#define EMPLOYEE_CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include "../Include/Models/Employee.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/DataStructures/SinglyLinkedList.h"

namespace EmployeeCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/employees.csv";
    }

    inline void WriteHeader() {
        std::ofstream File(GetFilePath(), std::ios::app);
        File.seekp(0, std::ios::end);
        if (File.tellp() == 0) {
            File << "Id,Name,LastName,Address,Salary,HireDate,Branch,Status\n";
        }
    }

    inline void Write(const Employee::Employee& E) {
        WriteHeader();

        std::ofstream File(GetFilePath(), std::ios::app);
        if (!File.is_open()) return;

        File << E.Id << ","
             << E.Name << ","
             << E.LastName << ","
             << E.Address << ","
             << E.Salary << ","
             << E.HireDate.Day << "/" << E.HireDate.Month << "/" << E.HireDate.Year << ","
             << E.BranchCode << ","
             << E.Status << "\n";
    }

    inline Singly::List<Employee::Employee> ReadAll() {
        auto list = Singly::Create<Employee::Employee>();

        std::ifstream File(GetFilePath());
        if (!File.is_open()) return list;

        std::string Line;
        std::getline(File, Line); // skip header

        while (std::getline(File, Line)) {
            std::stringstream ss(Line);
            std::string id, name, last, address, salStr, dateStr, branch, status;

            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, last, ',');
            std::getline(ss, address, ',');
            std::getline(ss, salStr, ',');
            std::getline(ss, dateStr, ',');
            std::getline(ss, branch, ',');
            std::getline(ss, status, ',');

            double salary = salStr.empty() ? 0.0 : std::stod(salStr);

            int d=0, m=0, y=0;
            sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y);

            Employee::Employee E{
                id, name, last, address,
                salary,
                {d, m, y},
                branch,
                status
            };

            Singly::PushBack(&list, E);
        }

        return list;
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
    }
}

#endif
