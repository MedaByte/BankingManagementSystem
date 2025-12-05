#ifndef EMPLOYEECSV_H
#define EMPLOYEECSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/Models/Employee.h"
#include "../Include/Models/Date.h"
#include "../Include/Utils/OriginPath.h"

namespace EmployeeCSV {

    // Get CSV file path | Pega o caminho do arquivo CSV
    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    // Trim whitespace from string | Remove espaços em branco da string
    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load employees from CSV | Carrega employees do CSV
    inline void Load(Employee::Employee employees[], int& count, const std::string& filename = "employees.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        // Check header | Verifica header
        if (!std::getline(file, line)) return;
        std::istringstream peek(line);
        std::string firstTok;
        std::getline(peek, firstTok, ',');
        bool isHeader = (firstTok.find_first_not_of("0123456789") != std::string::npos);
        if (!isHeader) {
            file.clear();
            file.seekg(0);
        }

        while (std::getline(file, line)) {
            if (trim(line).empty()) continue;
            std::istringstream ss(line);

            std::string id, name, lastName, address, salaryStr, hireDateStr, branchCode, status;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, lastName, ',');
            std::getline(ss, address, ',');
            std::getline(ss, salaryStr, ',');
            std::getline(ss, hireDateStr, ',');
            std::getline(ss, branchCode, ',');
            std::getline(ss, status, ',');

            id = trim(id);
            name = trim(name);
            lastName = trim(lastName);
            address = trim(address);
            salaryStr = trim(salaryStr);
            hireDateStr = trim(hireDateStr);
            branchCode = trim(branchCode);
            status = trim(status);

            double salary = 0.0;
            try { salary = std::stod(salaryStr); } catch(...) { salary = 0.0; }

            Date::Date hireDate = Date::FromString(hireDateStr);

            employees[count] = Employee::Create(name, lastName, address, salary, branchCode, id, hireDate, status);
            ++count;
            if (count >= 10000) break; // Safety limit | Limite de segurança
        }

        file.close();
    }

    // Write employees to CSV | Escreve employees no CSV
    inline void Write(Employee::Employee employees[], int count, const std::string& filename = "employees.csv") {
        std::ofstream file(GetFilePath() + filename, std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "Unable to open employees file for writing\n"; // Erro ao abrir arquivo
            return;
        }

        // Header | Cabeçalho
        file << "Id,Name,LastName,Address,Salary,HireDate,BranchCode,Status\n";
        for (int i = 0; i < count; ++i) {
            const auto& E = employees[i];
            file << E.Id << ","
                    << E.Name << ","
                    << E.LastName << ","
                    << E.Address << ","
                    << E.Salary << ","
                    << Date::ToString(E.HireDate) << ","
                    << E.BranchCode << ","
                    << E.Status << "\n";
        }

        file.close();
    }

} // namespace EmployeeCSV

#endif
