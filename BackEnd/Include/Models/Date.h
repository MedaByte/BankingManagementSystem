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
        std::tm LocalTime;

        #ifdef _WIN32
            localtime_s(&LocalTime, &t);
        #else
            localtime_r(&t, &localTime);
        #endif

        return Date{ LocalTime.tm_mday, LocalTime.tm_mon + 1, LocalTime.tm_year + 1900 };
    }

    inline Date FromString(const std::string& s) {
        int Day = 0, Month = 0, Year = 0;
        size_t firstSlash = s.find('/');
        size_t secondSlash = s.find('/', firstSlash + 1);

        if (firstSlash != std::string::npos && secondSlash != std::string::npos) {
            Day = std::stoi(s.substr(0, firstSlash));
            Month = std::stoi(s.substr(firstSlash + 1, secondSlash - firstSlash - 1));
            Year = std::stoi(s.substr(secondSlash + 1));
        }

        return Date{Day, Month, Year};
    }

    inline std::string ToString(const Date& d) {
        std::string sDay = (d.Day < 10 ? "0" : "") + std::to_string(d.Day);
        std::string sMonth = (d.Month < 10 ? "0" : "") + std::to_string(d.Month);
        std::string sYear = std::to_string(d.Year);

        return sDay + "/" + sMonth + "/" + sYear;
    }

    inline bool IsLeapYear(int Year) {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    inline int DaysInMonth(int Month, int Year) {
        switch (Month) {
            case 1:  return 31;
            case 2:  return IsLeapYear(Year) ? 29 : 28;
            case 3:  return 31;
            case 4:  return 30;
            case 5:  return 31;
            case 6:  return 30;
            case 7:  return 31;
            case 8:  return 31;
            case 9:  return 30;
            case 10: return 31;
            case 11: return 30;
            case 12: return 31;
            default: return 30;
        }
    }
    
    inline Date AddMonths(const Date& D, int Months){
        
        Date R = D;
        R.Month += Months;

        R.Year += (R.Month - 1) / 12;
        R.Month = ((R.Month - 1) % 12) + 1;

        int MaxDay = DaysInMonth(R.Month, R.Year);
        if (R.Day > MaxDay) R.Day = MaxDay;
        
        return R;
    }

    inline int CompareDates(const Date& D1, const Date& D2){
        auto toInt = [](const Date& d) {
            return d.Year * 10000 + d.Month * 100 + d.Day;
        };

        int val1 = toInt(D1);
        int val2 = toInt(D2);

        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }
}

#endif
