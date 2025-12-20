#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <fstream>      // For file operations | Para operações com arquivos
#include <sstream>      // For string streams | Para fluxos de string
#include <iomanip>      // For formatting numbers | Para formatar números
#include <string>       // For std::string | Para std::string
#include <iostream>     // For console output | Para saída no console

namespace Utils{

    // Generates a unique ID and stores the last used number | Gera um ID único e armazena o último número usado
    inline std::string GenerateId(const std::string& filepath, const std::string& prefix = "ACC"){
        int LastId = 0;  // Variable to store the last used ID | Variável para armazenar o último ID usado

        // Open file to read the last ID | Abre o arquivo para ler o último ID
        std::ifstream inFile(filepath);
        if (inFile){
            inFile >> LastId;  // Read the number from the file | Lê o número do arquivo
        }

        int NewId = LastId + 1;  // Increment to get a new ID | Incrementa para gerar um novo ID

        // Open file to save the new last ID | Abre o arquivo para salvar o novo último ID
        std::ofstream outFile(filepath);
        if (!outFile){
            // If writing fails, show error | Se escrever falhar, mostra erro
            std::cerr << "Couldn't open Id File for writing:" + filepath + ", PR=" + prefix;
            return "";
        }
        outFile << NewId;  // Save the new last ID in the file | Salva o novo último ID no arquivo

        // Build the final formatted ID string | Constrói a string final do ID formatado
        std::ostringstream oss;
        oss << prefix << std::setw(4) << std::setfill('0') << NewId;
        /*
            Example: ACC0001 if NewId = 1, CUS0012 if NewId = 12, EMP0456 if NewId = 456
            Exemplo: ACC0001 se NewId = 1, CUS0012 se NewId = 12, EMP0456 se NewId = 456
        */ 

        return oss.str();  // Return the formatted ID | Retorna o ID formatado
    }
}

#endif
