#ifndef ACCOUNTDESCRIPTION_H
#define ACCOUNTDESCRIPTION_H

#include <iostream>
#include <string>

using namespace std;

#include "architecture/auxiliary/time.h"
#include "accountOperation.h"

struct TimeInfo
{
    Time createTime;
    double ActivePeriod; // days
    TimeInfo(const Time &accountCreateTime):
        createTime(accountCreateTime),
        ActivePeriod(0.0)
    {
        Time now = Time::getNow();
        ActivePeriod = now - createTime;
    }

    friend std::ostream &operator << (std::ostream &out, const TimeInfo &timeInfo);
    friend std::istream &operator >> (std::istream &in, TimeInfo &timeInfo);
};

class AccountDescription
{
public:
    AccountDescription(const int accountID = AccountOperation::zeroID,
                       const std::string accountName = "unnamed",
                       const TimeInfo &accountTimeInfo = Time::getNow());

    friend ostream &operator << (ostream &out, const AccountDescription &description);
    friend istream &operator >> (istream &in, AccountDescription &description);

    int getID() const;
    const std::string getName() const;
    const TimeInfo &getTimeInfo() const;

    void print() const;
private:
    int ID;
    std::string name;
    TimeInfo timeInfo;

    static string replaceSpaces(const string &s);
    static string replaceUnderlines(const string &s);
};

#endif // ACCOUNTDESCRIPTION_H
