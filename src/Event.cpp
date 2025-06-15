#include "Event.hpp"
#include <iostream>
#include <algorithm>

Event::Event(Date date_, int start_time_, int duration_, string title_, string description_)
    : date(date_), start_time(start_time_), duration(duration_), title(title_), description(description_)
{
}
Date Event::getDate() const { return date; }
int Event::getStartTime() const { return start_time; }
int Event::getDuration() const { return duration; }
int Event::getId() const { return id; }
string Event::getTitle() const { return title; }
string Event::getDescription() const { return description; }
void Event::setId(int id_) { id = id_; }

PeriodicEvent::PeriodicEvent(Date start_date_, Date end_date_, int start_time_, int duration_, string title_, string description_, HolidayManager &holiday_manager_)
    : start_date(start_date_), end_date(end_date_), start_time(start_time_), duration(duration_), title(title_), description(description_), holiday_manager(holiday_manager_), has_holiday(0)
{
}

WeeklyEvent::WeeklyEvent(Date start_date_, Date end_date_, int start_time_, int duration_, vector<string> week_days_, string title_, string description_, HolidayManager &holiday_manager_)
    : PeriodicEvent(start_date_, end_date_, start_time_, duration_, title_, description_, holiday_manager_),
      week_days(week_days_)
{
    Date current_date = start_date;
    while (current_date <= end_date)
    {
        string current_day = date_utilities.getWeekDay(current_date);
        if (holiday_manager.isHoliday(current_date))
        {
            has_holiday = 1;
            date_utilities.goToNextDay(current_date);
        }
        else
        {
            if (find(week_days.begin(), week_days.end(), current_day) != week_days.end())
            {
            dates.push_back(current_date);
            }
            date_utilities.goToNextDay(current_date);
        }
    }
}

vector<Date> &PeriodicEvent::getDates() { return dates; }
int PeriodicEvent::getStartTime() const { return start_time; }
int PeriodicEvent::getDuration() const { return duration; }
int PeriodicEvent::getId() const { return id; }
int PeriodicEvent::getHasHoliday() const { return has_holiday; }
string PeriodicEvent::getTitle() const { return title; }
string PeriodicEvent::getDescription() const { return description; }
void PeriodicEvent::setId(int id_) { id = id_; }