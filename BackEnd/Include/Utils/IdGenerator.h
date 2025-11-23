#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

namespace Utils{

    inline std::string GenerateId(const std::string& filepath, const std::string& prefix = "ACC"){
        int LastId = 0;

        std::ifstream inFile(filepath);
        if (inFile){
            inFile >> LastId;
        }

        int NewId = LastId + 1;

        std::ofstream outFile(filepath);
        if (!outFile){
            throw std::runtime_error("Couldn't open Id File for writing:" + filepath + ", PR=" + prefix);
        }
        outFile << NewId;

        std::ostringstream oss;
        oss << prefix << std::setw(4) << std::setfill('0') << NewId;

        return oss.str();
    }
}

#endif