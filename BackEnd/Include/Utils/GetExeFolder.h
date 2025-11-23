#ifndef EXEPATH_H
#define EXEPATH_H

#include <windows.h>
#include <string>

namespace Utils {

    inline std::string getExeFolder() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string path(buffer);
        size_t pos = path.find_last_of("\\/");
        
        return path.substr(0, pos);
    }

}

#endif