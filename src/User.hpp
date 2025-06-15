#ifndef USER_HPP
#define USER_HPP

#include "Event.hpp"
#include "Task.hpp"
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class User
{
public:
    User(string username_, string password_);
    string getUsername() const;
    string getPassword() const;

    void addEvent(shared_ptr<Event> event);
    void addPeriodicEvent(shared_ptr<PeriodicEvent> periodic_event);
    void addTask(shared_ptr<Task> task);
    void deleteTask(int id);
    void editTask(shared_ptr<Task>, Date date, string date_str, int time, string title, string description);

    vector<shared_ptr<Event>> &getEvents();
    vector<shared_ptr<PeriodicEvent>> &getPeriodicEvents();
    vector<shared_ptr<Task>> &getTasks();

private:
    string username;
    string password;

    int event_count;
    vector<shared_ptr<Event>> events;

    int periodic_event_count;
    vector<shared_ptr<PeriodicEvent>> periodic_events;

    int task_count;
    vector<shared_ptr<Task>> tasks;
};

#endif