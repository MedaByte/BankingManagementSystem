#ifndef ORIGINPATH_H
#define ORIGINPATH_H

#include <windows.h> // Windows API for file paths | API do Windows para caminhos de arquivos
#include <string>    // For std::string | Para std::string

namespace Utils
{

    inline int monthDifference(int startMonth, int endMonth)
    {
        if (endMonth >= startMonth)
            return endMonth - startMonth;
        else
            return (12 - startMonth) + endMonth;
    }

    // Returns the root folder of the project | Retorna a pasta raiz do projeto
    inline std::string GetOriginFolder()
    {
        char buffer[MAX_PATH];                      // Buffer to store the executable path | Buffer para armazenar o caminho do executável
        GetModuleFileNameA(NULL, buffer, MAX_PATH); // Get the path of the running executable | Obtém o caminho do executável em execução
        std::string path(buffer);                   // Convert to std::string | Converte para std::string

        // Look for the project folder name in the path | Procura o nome da pasta do projeto no caminho
        size_t pos = path.find("BankingManagementSystem");
        if (pos == std::string::npos)
        {
            // If folder not found, throw an error | Se a pasta não for encontrada, lança um erro
            throw std::runtime_error("Origin folder not found in executable path");
        }

        // Return the path up to the project folder | Retorna o caminho até a pasta do projeto
        return path.substr(0, pos + std::string("BankingManagementSystem").length());
    }

}

#endif
