#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H
#include "../Models/Employee.h"
#include "../CSV/EmployeeCSV.h"
#include "../Utils/OriginPath.h"
#include <string>

namespace EmployeeController {
    inline bool Create(const Employee::Employee &E){
        if(E.Name.empty() || E.LastName.empty()) return false;
        EmployeeCSV::Write(E);
        return true;
    }

    inline bool ChangeSalary(Employee::Employee* E, double NewSalary){
        if(!E) return false;
        E->Salary = NewSalary;
        return true;
    }

    inline bool ChangeStatus(Employee::Employee* E, const std::string& NewStatus){
        if(!E) return false;
        E->Status = NewStatus;
        return true;
    }
}
#endif
