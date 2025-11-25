#ifndef DATE_H
#define DATE_H

#include <string>
#include <iomanip>
#include <sstream>

namespace Date{
    
    struct Date {
        int Day;
        int Month;
        int Year;
    };
    
    inline std::string GetDay(const Date& D){
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << D.Day;
        return oss.str();
    }
    
    inline std::string GetMonth(const Date& D){
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << D.Month;
        return oss.str();
    }
    
    inline Date Now() {
        std::time_t t = std::time(nullptr);
        std::tm* localTime = std::localtime(&t);

        return Date{ localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900 };
    }

    inline std::string ToString(const Date& D) {
        return std::to_string(D.Year) + "-" + GetMonth(D) + "-" + GetDay(D);
    }
}

#endif
