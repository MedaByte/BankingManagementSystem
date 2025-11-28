#ifndef LOAN_CSV_H
#define LOAN_CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Include/Models/Loan.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/DataStructures/SinglyLinkedList.h"

namespace LoanCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/loans.csv";
    }

    inline void Write(const Loan::Loan& L) {
        std::ofstream File(GetFilePath(), std::ios::app);
        if(File.is_open()) {
            File << L.Id << "," 
                    << L.Amount << "," 
                    << L.InterestRate << ","
                    << L.StartDate.Day << "/" << L.StartDate.Month << "/" << L.StartDate.Year << ","
                    << L.EndDate.Day << "/" << L.EndDate.Month << "/" << L.EndDate.Year << ","
                    << L.Status << "\n";
            File.close();
        }
    }

    inline Singly::List<Loan::Loan> ReadAll() {
        Singly::List<Loan::Loan> list = Singly::Create<Loan::Loan>();

        std::ifstream File(GetFilePath());
        if (!File.is_open()) return list;

        std::string Line;
        while (std::getline(File, Line)) {
            std::stringstream ss(Line);

            std::string id, amountStr, rateStr, startDateStr, endDateStr, status;

            std::getline(ss, id, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, rateStr, ',');
            std::getline(ss, startDateStr, ',');
            std::getline(ss, endDateStr, ',');
            std::getline(ss, status, ',');

            double amount = 0.0, rate = 0.0;
            try {
                if (!amountStr.empty()) amount = std::stod(amountStr);
            }
            catch(const std::exception& e) {
                std::cerr << "Invalid amount '" << amountStr << "' for Loan ID " << id << ". Defaulting to 0.\n";
                amount = 0.0;
            }

            try {
                if (!rateStr.empty()) rate = std::stod(rateStr);
            }
            catch(const std::exception& e) {
                std::cerr << "Invalid interest rate '" << rateStr << "' for Loan ID " << id << ". Defaulting to 0.\n";
                rate = 0.0;
            }

            int sd = 0, sm = 0, sy = 0;
            int ed = 0, em = 0, ey = 0;

            sscanf(startDateStr.c_str(), "%d/%d/%d", &sd, &sm, &sy);
            sscanf(endDateStr.c_str(), "%d/%d/%d", &ed, &em, &ey);

            Loan::Loan L{
                id,
                amount,
                rate,
                {sd, sm, sy},
                {ed, em, ey},
                status
            };

            Singly::PushBack(&list, L);
        }

        return list;
    }

    inline void Clear() {
        std::ofstream File(GetFilePath(), std::ios::trunc);
        File.close();
    }

}

#endif
