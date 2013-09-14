#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <QDateTime>

using namespace std;

class Time
{
public:
    Time();
    Time(const int nYear, const int nMonth, const int nDay, const int nHour, const int nMinute);
    Time(const QDateTime &qDateTime);

    void set(const int nYear, const int nMonth, const int nDay, const int nHour, const int nMinute);
    void print() const;
    void println() const;

    friend ostream &operator << (ostream &os, const Time &time);
    friend istream &operator >> (istream &is, Time &time);
    friend double operator - (const Time &end, const Time &begin);

    static Time getDefaultTime();
    static Time getNow();
private:
    static const int defaultYear = 2000;
    static const int defaultMonth = 1;
    static const int defaultDay = 1;
    static const int defaultHour = 0;
    static const int defaultMinute = 0;
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

#endif // TIME_H
