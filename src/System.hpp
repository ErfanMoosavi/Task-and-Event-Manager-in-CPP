#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "User.hpp"
#include <iostream>

const int MIN_HOUR = 0;
const int MAX_HOUR = 23;

using namespace std;

enum class Status
{
    ok,
    empty,
    not_found,
    bad_request,
    permission_denied,
    holiday_found,
    overlap
};

struct ReportItem
{
    Date date;
    int time;
    int priority;
    int id;
    string type;
    string title;
    string description;
    int duration;

    ReportItem(Date d, int t, int p, int i, string ty,
               string ti, string desc, int dur)
        : date(d), time(t), priority(p), id(i), type(ty),
          title(ti), description(desc),
          duration(dur) {}
};

class System
{
public:
    System(HolidayManager &holiday_manager_);
    Status signup(string username, string password);
    Status login(string username, string password);
    Status logout();
    Status addEvent(string date_str, int start_time, int duration, string title, string description);
    Status addWeeklyEvent(string start_date_str, string end_date_str, int start_time, int duration, string week_days, string title, string description);
    Status addTask(string date_str, int time, string title, string description);
    Status deleteTask(int id);
    Status editTask(int id, string date_str, int time, string title, string description);

    Status generateReportItems(string start_date_str, string end_date_str);
    void gatherReportItems(Date from, Date to);
    void sortReportItems();
    string getReportHTML(const string &username) const;
    vector<string> extractDaysOfWeek(string week_days_str);
    bool isOverlap(Date &date, int start_time, int duration) const;
    shared_ptr<User> findUser(string username) const;
    shared_ptr<Task> findTask(int id) const;
    shared_ptr<User> getLoggedInUser() const;

private:
    DateUtilities date_utilities;
    HolidayManager &holiday_manager;
    vector<shared_ptr<User>> users;
    shared_ptr<User> logged_in_user;
    vector<ReportItem> report_items;
};

#endif