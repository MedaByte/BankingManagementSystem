#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../Utils/IdGenerator.h"
#include "../Utils/OriginPath.h"
#include "Date.h"

namespace Employee {

    struct Employee {
        std::string Id;
        std::string Name;
        std::string LastName;
        std::string Address;
        double Salary;
        Date::Date HireDate;
        std::string BranchCode;
        std::string Status;
    };

    inline Employee Create(
        const std::string& Name,
        const std::string& LastName,
        const std::string& Address,
        double Salary,
        const std::string& BranchCode,
        std::string Id = Utils::GenerateId(Utils::GetOriginFolder() + "/BackEnd/Data/last_employee_id.txt", "EMP"),
        const Date::Date& HireDate = Date::Now(),
        const std::string& Status = "active"
    ) {
        Employee NewEmployee{
            Id,
            Name,
            LastName,
            Address,
            Salary,
            HireDate,
            BranchCode,
            Status
        };

        return NewEmployee;
    }


    inline void ChangeSalary(Employee* E, double NewSalary) {
        E->Salary = NewSalary;
    }

    inline void ChangeAddress(Employee* E, const std::string& NewAddress) {
        E->Address = NewAddress;
    }

    inline void ChangeBranch(Employee* E, const std::string& NewBranch) {
        E->BranchCode = NewBranch;
    }

    inline void ChangeStatus(Employee* E, const std::string& NewStatus) {
        E->Status = NewStatus;
    }

    inline void Display(const Employee& E) {
        std::cout << "Employee ID: " << E.Id << "\n";
        std::cout << "Name: " << E.Name << " " << E.LastName << "\n";
        std::cout << "Address: " << E.Address << "\n";
        std::cout << "Salary: " << std::fixed << std::setprecision(2) << E.Salary << " TND\n";
        std::cout << "Hire Date: " << Date::GetDay(E.HireDate) << "/" 
                    << Date::GetMonth(E.HireDate) << "/" << E.HireDate.Year << "\n";
        std::cout << "Branch Code: " << E.BranchCode << "\n";
        std::cout << "Status: " << E.Status << "\n";
    }

}

#endif
