#include "Task.hpp"

Task::Task(Date date_, int time_, string title_, string description_)
    : date(date_), time(time_), title(title_), description(description_)
{
}

int Task::getId() const { return id; }
Date Task::getDate() const { return date; }
int Task::getTime() const { return time; }
string Task::getTitle() const { return title; }
string Task::getDescription() const { return description; }

void Task::setId(int id_) { id = id_; }
void Task::setDate(int day, int month, int year) { date.setDate(day, month, year); }
void Task::setTime(int time_) { time = time_; }
void Task::setTitle(string title_) { title = title_; }
void Task::setDescription(string description_) { description = description_; }