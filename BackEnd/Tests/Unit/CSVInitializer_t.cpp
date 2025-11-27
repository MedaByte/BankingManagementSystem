#include <iostream>
#include "../../Include/Utils/CSVInitializer.h"

int main() {
    
    std::cout << "Initializing CSV files...\n";
    Utils::InitializeCSVFiles();
    std::cout << "Initialization complete.\n";

    return 0;
}
