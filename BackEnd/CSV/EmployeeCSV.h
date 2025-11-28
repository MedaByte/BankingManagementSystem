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

    inline void Write(const Employee::Employee& E) {
        std::ofstream File(GetFilePath(), std::ios::app);
        if(File.is_open()) {
            File << E.Id << "," << E.Name << "," << E.LastName << "," << E.Address << "," << E.Salary << ","
                    << E.HireDate.Day << "/" << E.HireDate.Month << "/" << E.HireDate.Year << "," << E.BranchCode << "," << E.Status << "\n";
            File.close();
        }
    }

    inline Singly::List<Employee::Employee> ReadAll(){
        auto List = Singly::Create<Employee::Employee>();
        std::ifstream File(GetFilePath());
        if(!File.is_open()) return List;

        std::string Line;
        while(std::getline(File, Line)){
            std::stringstream ss(Line);
            std::string id, name, last, address, salaryStr, dateStr, branch, status;

            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, last, ',');
            std::getline(ss, address, ',');
            std::getline(ss, salaryStr, ',');
            std::getline(ss, dateStr, ',');
            std::getline(ss, branch, ',');
            std::getline(ss, status, ',');

            int d, m, y;
            sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y);

            double salary = 0.0;
            try {
                if (!salaryStr.empty()) {
                    salary = std::stod(salaryStr);
                }
            } 
            catch (const std::exception& e) {
                std::cerr << "Invalid Salary value '" << salaryStr << "' in CSV. Setting to 0.\n";
                salary = 0.0;
            }

            Employee::Employee E{
                id,
                name,
                last,
                address,
                salary,
                {d, m, y},
                branch,
                status
            };
            std::cout << "test;";
            Singly::PushBack(&List, E);
        }

        File.close();
        return List;
    }


    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }
}
#endif
