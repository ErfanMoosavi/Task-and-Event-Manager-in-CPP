#ifndef TASK_HPP
#define TASK_HPP

#include "Date.hpp"
#include <string>
#include <vector>

using namespace std;

class Task
{
public:
    Task(Date date_, int time_, string title_, string description_);
    int getId() const;
    Date getDate() const;
    int getTime() const;
    string getTitle() const;
    string getDescription() const;
    void setId(int id_);
    void setDate(int day, int month, int year);
    void setTime(int time_);
    void setTitle(string title_);
    void setDescription(string description_);

private:
    int id;
    Date date;
    int time;
    string title;
    string description;
};

#endif