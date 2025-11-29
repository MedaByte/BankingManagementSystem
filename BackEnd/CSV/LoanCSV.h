#ifndef LOAN_CSV_H
#define LOAN_CSV_H

#include <fstream>
#include <sstream>
#include "../Include/Models/Loan.h"
#include "../Include/Utils/OriginPath.h"
#include "../Include/DataStructures/SinglyLinkedList.h"

namespace LoanCSV {

    inline std::string GetFilePath() {
        return Utils::GetOriginFolder() + "/BackEnd/Data/loans.csv";
    }

    inline void WriteHeader() {
        std::ofstream File(GetFilePath(), std::ios::app);
        File.seekp(0, std::ios::end);
        if (File.tellp() == 0) {
            File << "Id,Amount,Rate,StartDate,EndDate,Status\n";
        }
    }

    inline void Write(const Loan::Loan& L) {
        WriteHeader();
        std::ofstream File(GetFilePath(), std::ios::app);

        File << L.Id << ","
             << L.Amount << ","
             << L.InterestRate << ","
             << L.StartDate.Day << "/" << L.StartDate.Month << "/" << L.StartDate.Year << ","
             << L.EndDate.Day << "/" << L.EndDate.Month << "/" << L.EndDate.Year << ","
             << L.Status << "\n";
    }

    inline Singly::List<Loan::Loan> ReadAll() {
        auto list = Singly::Create<Loan::Loan>();

        std::ifstream File(GetFilePath());
        if (!File.is_open()) return list;

        std::string Line;
        std::getline(File, Line); // skip header

        while (std::getline(File, Line)) {
            std::stringstream ss(Line);
            std::string id, amountStr, rateStr, sdStr, edStr, status;

            std::getline(ss, id, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, rateStr, ',');
            std::getline(ss, sdStr, ',');
            std::getline(ss, edStr, ',');
            std::getline(ss, status, ',');

            double amount = amountStr.empty() ? 0.0 : std::stod(amountStr);
            double rate   = rateStr.empty() ? 0.0 : std::stod(rateStr);

            int sd=0, sm=0, sy=0;
            int ed=0, em=0, ey=0;

            sscanf(sdStr.c_str(), "%d/%d/%d", &sd, &sm, &sy);
            sscanf(edStr.c_str(), "%d/%d/%d", &ed, &em, &ey);

            Loan::Loan L{
                id, amount, rate,
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
    }
}

#endif
