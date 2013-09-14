#include "time.h"

Time::Time()
{
    *this = getDefaultTime();
}

Time::Time(const int nYear = defaultYear,
           const int nMonth = defaultMonth,
           const int nDay = defaultDay,
           const int nHour = defaultHour,
           const int nMinute = defaultMinute):
    year(nYear),
    month(nMonth),
    day(nDay),
    hour(nHour),
    minute(nMinute)
{
}

Time::Time(const QDateTime &qDateTime)
{
    QDate qDate = qDateTime.date();
    QTime qTime = qDateTime.time();
    *this = Time(qDate.year(), qDate.month(), qDate.day(), qTime.hour(), qTime.minute());
}

void Time::set(const int nYear = defaultYear,
               const int nMonth = defaultMonth,
               const int nDay = defaultDay,
               const int nHour = defaultHour,
               const int nMinute = defaultMinute)
{
    *this = Time(nYear, nMonth, nDay, nHour, nMinute);
}

void Time::print() const
{
    cout << "time("
         << (hour < 10 ? "0" : "") << hour << ":"
         << (minute < 10 ? "0" : "") << minute << " "
         << (day < 10 ? "0" : "") << day << "."
         << (month < 10 ? "0" : "") << month << "." << year << ")";
}

void Time::println() const
{
    cout << (*this) << endl;
}

ostream &operator << (ostream &os, const Time &time)
{
    os << time.year << " " << time.month << " " << time.day << " " << time.hour << " " << time.minute;
    return os;
}

istream &operator >> (istream &is, Time &time)
{
    is >> time.year >> time.month >> time.day >> time.hour >> time.minute;
    return is;
}

Time Time::getDefaultTime()
{
    return Time(defaultYear, defaultMonth, defaultDay, defaultHour, defaultMinute);
}

Time Time::getNow()
{
    QDateTime dt = QDateTime::currentDateTime();
    QDate date = dt.date();
    QTime time = dt.time();
    return Time(date.year(), date.month(), date.day(), time.hour(), time.minute());
}

double operator - (const Time &end, const Time &begin)
{
    double dYears = (end.year - begin.year) * 365.0;
    double dMonths = (end.month - begin.month) * 29.4;
    double dDays = end.day - begin.day;
    double dHours = (end.hour - begin.hour) / 24;
    double dMinutes = (end.minute - begin.minute) / (24 * 60);
    double result = dYears + dMonths + dDays + dHours + dMinutes;
    return result;
}
