#include<iostream>
#include "Cpp JSON Methods/jsonToCpp.cpp"
using namespace std ;

void main(){
    string command;
    getline(cin, command); 

    json j = json::parse(command);
    

}