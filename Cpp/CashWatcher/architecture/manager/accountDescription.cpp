#include "accountDescription.h"

AccountDescription::AccountDescription(const int accountID,
                                       const std::string accountName,
                                       const TimeInfo &accountTimeInfo):
    ID(accountID),
    name(replaceSpaces(accountName)),
    timeInfo(accountTimeInfo)
{
}

std::ostream &operator << (std::ostream &out, const AccountDescription &description)
{
    out << description.ID << endl << description.name << endl << description.timeInfo;
    return out;
}

std::istream &operator >> (std::istream &in, AccountDescription &description)
{
    in >> description.ID >> description.name >> description.timeInfo;
    return in;
}

string AccountDescription::replaceSpaces(const string &s)
{
    string result = "";
    for (int i = 0; i < static_cast<int> (s.length()); ++i)
    {
        result += (s[i] == ' ' ? '_' : s[i]);
    }
    return result;
}

string AccountDescription::replaceUnderlines(const string &s)
{
    string result = "";
    for (int i = 0; i < static_cast<int> (s.length()); ++i)
    {
        result += (s[i] == '_' ? ' ' : s[i]);
    }
    return result;
}

ostream &operator << (ostream &out, const TimeInfo &timeInfo)
{
    out << timeInfo.createTime;
    return out;
}

istream &operator >> (istream &in, TimeInfo &timeInfo)
{
    in >> timeInfo.createTime;
    timeInfo = TimeInfo(timeInfo.createTime);
    return in;
}

int AccountDescription::getID() const
{
    return ID;
}

const string AccountDescription::getName() const
{
    return replaceUnderlines(name);
}

const TimeInfo &AccountDescription::getTimeInfo() const
{
    return timeInfo;
}

void printTimeInfo(TimeInfo timeInfo)
{
    cout << "TimeInfo(create ";
    timeInfo.createTime.print();
    cout.precision(3);
    cout << "; active during " << fixed << timeInfo.ActivePeriod << " days)";
}

void AccountDescription::print() const
{
    cout << "AccountInfo(#" << ID
         << " name: \"" << replaceUnderlines(name)
         << "\" ";
    printTimeInfo(timeInfo);
    cout << ")" << endl;
}
