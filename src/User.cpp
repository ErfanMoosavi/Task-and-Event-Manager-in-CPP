#include "User.hpp"

User::User(string username_, string password_)
    : username(username_), password(password_), event_count(1), periodic_event_count(1), task_count(1)
{
}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }

void User::addEvent(shared_ptr<Event> event)
{
    event->setId(event_count);
    events.push_back(event);
    event_count++;
}

void User::addPeriodicEvent(shared_ptr<PeriodicEvent> periodic_event)
{
    periodic_event->setId(periodic_event_count);
    periodic_events.push_back(periodic_event);
    periodic_event_count++;
}

void User::addTask(shared_ptr<Task> task)
{
    task->setId(task_count);
    tasks.push_back(task);
    task_count++;
}

void User::deleteTask(int id)
{
    auto it = remove_if(tasks.begin(), tasks.end(), [id](const shared_ptr<Task> &t)
                        { return t->getId() == id; });
    tasks.erase(it, tasks.end());
}

void User::editTask(shared_ptr<Task> task, Date date, string date_str, int time, string title, string description)
{
    task->setDate(date_str == "" ? task->getDate().getDay() : date.getDay(), date_str == "" ? task->getDate().getMonth() : date.getMonth(), date_str == "" ? task->getDate().getYear() : date.getYear());
    task->setTime(time == -1 ? task->getTime() : time);
    task->setTitle(title == "" ? task->getTitle() : title);
    task->setDescription(description == "" ? task->getDescription() : description);
}

vector<shared_ptr<Event>> &User::getEvents() { return events; }
vector<shared_ptr<PeriodicEvent>> &User::getPeriodicEvents() { return periodic_events; }
vector<shared_ptr<Task>> &User::getTasks() { return tasks; }