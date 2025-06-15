#ifndef DATE_HPP
#define DATE_HPP

using namespace std;

class Date
{
public:
    Date();
    Date(int day_, int month_, int year_);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDate(int day_, int month_, int year_);
    bool operator<=(const Date &other) const;

private:
    int day;
    int month;
    int year;
    bool is_holiday;
};

#endif