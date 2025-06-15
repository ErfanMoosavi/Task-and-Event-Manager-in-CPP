#include "HolidayManager.hpp"

DateUtilities date_utilities;

void HolidayManager::loadFromCSV(const string &filename)
{
    ifstream file(filename);
    string line;

    if (!file.is_open())
        return;

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        vector<int> values;

        while (getline(ss, token, ','))
            values.push_back(stoi(token));

        holidays.push_back(Date(values[0], values[1], values[2]));
    }
}

bool HolidayManager::isHoliday(const Date &date)
{
    for (const auto &holiday : holidays)
    {
        if (date_utilities.isSameDate(date, holiday))
            return true;
    }
    return false;
}