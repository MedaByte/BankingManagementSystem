#ifndef CUSTOMERCSV_H
#define CUSTOMERCSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/Models/Customer.h"
#include "../Include/Utils/OriginPath.h"

namespace CustomerCSV {

    // Get CSV file path | Obter caminho do CSV
    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/";
    }

    // Trim whitespace | Remover espaços em branco
    inline std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    // Load customers from CSV | Carregar clientes do CSV
    inline void Load(Customer::Customer customers[], int& count, const std::string& filename = "customers.csv") {
        std::ifstream file(GetFilePath() + filename);
        if (!file.is_open()) return;

        std::string line;
        count = 0;

        // Check header | Verificar cabeçalho
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
            
            std::string id, name, lastName, address, phone;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, lastName, ',');
            std::getline(ss, address, ',');
            std::getline(ss, phone, ',');
            
            id = trim(id);
            name = trim(name);
            lastName = trim(lastName);
            address = trim(address);
            phone = trim(phone);
            
            customers[count] = Customer::Create(name, lastName, address, phone, id);
            ++count;
            
            if (count >= 10000) break; // safety | segurança
        }
        
        file.close();
    }
    // Write customers to CSV | Escrever clientes no CSV
    inline void Write(Customer::Customer customers[], int count, const std::string& filename = "customers.csv") {
        std::ofstream file(GetFilePath() + filename, std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "Unable to open customers file for writing\n";
            return;
        }

        // Header | Cabeçalho
        file << "Id,Name,LastName,Address,Phone\n";

        for (int i = 0; i < count; ++i) {
            const auto& C = customers[i];
            file << C.Id << ","
                    << C.Name << ","
                    << C.LastName << ","
                    << C.Address << ","
                    << C.Phone << "\n";
        }

        file.close();
    }

} // namespace CustomerCSV

#endif
