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
        std::string Id;        // Employee ID | ID do employee
        std::string Name;      // First name | Primeiro nome
        std::string LastName;  // Last name | Último nome
        std::string Address;   // Address | Endereço
        double Salary;         // Salary | Salário
        Date::Date HireDate;   // Hire date | Data de contratação
        std::string BranchCode;// Branch code | Código da branch
        std::string Status;    // Status (active/inactive) | Status (ativo/inativo)
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

        return NewEmployee; // Return new employee | Retornar novo employee
    }

    inline void ChangeSalary(Employee* E, double NewSalary) {
        E->Salary = NewSalary;
        // Update salary | Atualizar salário
    }

    inline void ChangeAddress(Employee* E, const std::string& NewAddress) {
        E->Address = NewAddress;
        // Update address | Atualizar endereço
    }

    inline void ChangeBranch(Employee* E, const std::string& NewBranch) {
        E->BranchCode = NewBranch;
        // Update branch | Atualizar branch
    }

    inline void ChangeStatus(Employee* E, const std::string& NewStatus) {
        E->Status = NewStatus;
        // Update status | Atualizar status
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
        // Display employee info | Mostrar informações do employee
    }

}

#endif
