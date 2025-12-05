#include "../../Include/Utils/IdGenerator.h"
#include "../../Include/Utils/OriginPath.h"

#include <iostream>

int main() {
    try {

        std::string exeFolder = Utils::GetOriginFolder();
        
        std::string dataFolder = exeFolder + "/BackEnd/Data/";

        std::string accId1 = Utils::GenerateId(dataFolder + "last_account_id.txt", "ACC");
        std::cout << "Generated Account ID: " << accId1 << "\n";

        std::string accId2 = Utils::GenerateId(dataFolder + "last_account_id.txt", "ACC");
        std::cout << "Generated Account ID: " << accId2 << "\n";

        std::string loanId = Utils::GenerateId(dataFolder + "last_loan_id.txt", "LOAN");
        std::cout << "Generated Loan ID: " << loanId << "\n";

        std::string transId = Utils::GenerateId(dataFolder + "last_trans_id.txt", "TRANS");
        std::cout << "Generated Transaction ID: " << transId << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
