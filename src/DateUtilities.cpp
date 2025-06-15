#include "DateUtilities.hpp"
#include <iostream>
Date DateUtilities::stringToDate(const string &date_str)
    const
{
    if (date_str == "")
        return Date();

    int year = stoi(date_str.substr(0, 4));
    int month = stoi(date_str.substr(5, 2));
    int day = stoi(date_str.substr(8, 2));
    return Date(day, month, year);
}

string DateUtilities::dateToString(const Date &date)
    const
{
    return to_string(date.getYear()) + "/" +
           (date.getMonth() < 10 ? "0" : "") + to_string(date.getMonth()) + "/" +
           (date.getDay() < 10 ? "0" : "") + to_string(date.getDay());
}

string DateUtilities::getWeekDay(const Date &date)
{
    vector<string> weekdays = {"Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"};
    Date origin(1, 1, 1404);
    int days = computeDateDistance(origin, date);
    return weekdays[(days % 7)];
}

int DateUtilities::computeDateDistance(Date first_date, Date second_date)
{
    int distance = 0;
    while (!isSameDate(first_date, second_date))
    {
        goToNextDay(first_date);
        distance++;
    }
    return distance;
}

void DateUtilities::goToNextDay(Date &date)
{
    int day = date.getDay();
    int month = date.getMonth();
    int year = date.getYear();
    if (day == DAYS_IN_MONTH && month == MONTHS_IN_YEAR)
        date.setDate(1, 1, year + 1);
    else if (day == DAYS_IN_MONTH && month != MONTHS_IN_YEAR)
        date.setDate(1, month + 1, year);
    else
        date.setDate(day + 1, month, year);
}

bool DateUtilities::isSameDate(Date first_date, Date second_date)
    const
{
    if (first_date.getDay() == second_date.getDay() &&
        first_date.getMonth() == second_date.getMonth() &&
        first_date.getYear() == second_date.getYear())
        return true;
    return false;
}