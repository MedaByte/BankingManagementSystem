#ifndef ORIGINPATH_H
#define ORIGINPATH_H

#include <windows.h>
#include <string>

namespace Utils {

    inline std::string GetOriginFolder() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string path(buffer);

        size_t pos = path.find("BankingManagementSystem");
        if (pos == std::string::npos) {
            throw std::runtime_error("Origin folder not found in executable path");
        }

        return path.substr(0, pos + std::string("BankingManagementSystem").length());
    }

}

#endif
