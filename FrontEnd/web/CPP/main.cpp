#include<iostream>
#include "Cpp JSON Methods/jsonToCpp.h"
#include "Cpp JSON Methods/CppToJson.h"
#include <typeinfo> 
using namespace std ;

int main(){
    cerr<<"                New Run             "<<endl<<endl<<endl<<endl ;
    string input;
    getline(cin, input);
    std::cerr<< "Received input:   " << input << std::endl;
    json j = json::parse(input);
    
    string command = j["command"].get<string>();
    string info = j["info"].get<string>();

    std::cerr<< "J is good  " <<endl ;
    std::cerr<< "Command : "<< command  << std::endl;
    std::cerr<< "Info : "<< info  << std::endl;

    if(command == "Load All Accounts"){
        std::cerr<< "Loading All Accounts :   "<<StringifyAllAccounts()<<endl ;
        std::cout<< StringifyAllAccounts()<<endl ;
    }
    else if (command == "Load All Employees"){
        std::cout<< StringifyAllEmployees()<<endl ;
    }
    else if (command == "Load Account"){
        cerr<<"account of id" << info << "is: "<<StringifyAccount(info);
        std::cout<< StringifyAccount(info)<<endl ;
    }
    return 0 ;
}