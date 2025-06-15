#include "Date.hpp"

Date::Date()
    : day(1), month(1), year(1404)
{
}

Date::Date(int day_, int month_, int year_)
    : day(day_), month(month_), year(year_)
{
}

int Date::getDay() const { return day; }

int Date::getMonth() const { return month; }

int Date::getYear() const { return year; }

void Date::setDate(int day_, int month_, int year_)
{
    day = day_;
    month = month_;
    year = year_;
}

bool Date::operator<=(const Date &other) const
{
    if (year != other.year)
        return year < other.year;
    if (month != other.month)
        return month < other.month;
    return day <= other.day;
}