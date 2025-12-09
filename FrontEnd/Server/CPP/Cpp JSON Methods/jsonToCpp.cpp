#include <iostream>
#include "jsonToCpp.h"
using namespace std ;

string*JSONArraytoCppArrayOfStrings(const json&j) {
    int ln = j.size() ;
    string*arr = new string[ln];
    for(int i = 0 ; i<ln ; i++){
        arr[i] = j[i].get<string>() ;
    }
    return arr ;
}
