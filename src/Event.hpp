#ifndef EVENT_HPP
#define EVENT_HPP

#include "DateUtilities.hpp"
#include "HolidayManager.hpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Event
{
public:
    Event(Date date_, int start_time_, int duration_, string title_, string description_);
    Date getDate() const;
    int getStartTime() const;
    int getDuration() const;
    int getId() const;
    string getTitle() const;
    string getDescription() const;
    void setId(int id_);

private:
    int id;
    Date date;
    int start_time;
    int duration;
    string title;
    string description;
    DateUtilities date_utilities;
};

class PeriodicEvent
{
public:
    virtual ~PeriodicEvent() = default;
    PeriodicEvent(Date start_date_, Date end_date_, int start_time_, int duration_, string title_, string description_, HolidayManager &holiday_manager_);
    vector<Date> &getDates();
    int getStartTime() const;
    int getDuration() const;
    int getId() const;
    int getHasHoliday() const;
    string getTitle() const;
    string getDescription() const;
    void setId(int id_);

protected:
    int id;
    Date start_date;
    Date end_date;
    int start_time;
    int duration;
    string type;
    string title;
    string description;
    vector<Date> dates;
    DateUtilities date_utilities;
    HolidayManager &holiday_manager;
    int has_holiday;
};

class WeeklyEvent : public PeriodicEvent
{
public:
    WeeklyEvent(Date start_date_, Date end_date_, int start_time_, int duration_, vector<string> week_days, string title_, string description_, HolidayManager &holiday_manager_);

private:
    vector<string> week_days;
};

#endif