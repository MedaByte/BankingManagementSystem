#ifndef JSONTOCPP_H
#define JSONTOCPP_H
#include "json.hpp"
using json = nlohmann::json;
using namespace std ;

string*JSONArraytoCppArrayOfStrings(const json&j) ;






#endif
