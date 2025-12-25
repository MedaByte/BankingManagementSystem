#ifndef ORIGINPATH_H
#define ORIGINPATH_H

#include <string>
#include <stdexcept>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>   // For readlink
    #include <limits.h>   // For PATH_MAX
#endif

namespace Utils
{
    inline int monthDifference(int startMonth, int endMonth)
    {
        if (endMonth >= startMonth)
            return endMonth - startMonth;
        else
            return (12 - startMonth) + endMonth;
    }

    inline std::string GetOriginFolder()
{
    std::string path;

#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    path = std::string(buffer);
#else
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len == -1)
        throw std::runtime_error("Unable to get executable path");
    buffer[len] = '\0';
    path = std::string(buffer);
#endif

    // Convert path to lowercase for comparison
    std::string pathLower = path;
    
    std::string folderName = "DSA_Fn_save"; // lowercase
    size_t pos = pathLower.find(folderName);
    if (pos == std::string::npos)
        throw std::runtime_error("Origin folder not found in executable path");

    return path.substr(0, pos + folderName.length());
}


}

#endif
