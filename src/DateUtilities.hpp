#ifndef DATE_UTILITIES
#define DATE_UTILITIES

#include "Date.hpp"
#include <vector>
#include <string>

const int DAYS_IN_MONTH = 30;
const int MONTHS_IN_YEAR = 12;

class DateUtilities
{
public:
    Date stringToDate(const string &date_str) const;
    string dateToString(const Date &date) const;
    string getWeekDay(const Date &date);
    int computeDateDistance(Date first_date, Date second_date);
    void goToNextDay(Date &date);
    bool isSameDate(Date first_date, Date second_date) const;
};

#endif