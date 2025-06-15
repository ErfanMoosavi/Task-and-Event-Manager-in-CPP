#ifndef HOLIDAY_MANAGER
#define HOLIDAY_MANAGER

#include "Date.hpp"
#include "DateUtilities.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class HolidayManager
{
public:
    void loadFromCSV(const string &filename);
    bool isHoliday(const Date &date);

private:
    vector<Date> holidays;
};

#endif