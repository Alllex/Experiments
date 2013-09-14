#include "user.h"

User::User(const std::string newUserName)
{
    userName = newUserName;
    userPass = "";
}

User::~User()
{
    delete manager;
}

void User::changeUserName(const std::string &newUserName)
{
    userName = newUserName;
}

double User::peekCash(const int accountID) const
{
    return manager->peekCash(accountID);
}

void User::depositCash(const int accountID, const double payment, const Time &time)
{
    manager->makeOperation(opDeposit, accountID, payment, time);
}

void User::payoutCash(const int accountID, const double payment, const Time &time)
{
    manager->makeOperation(opPayout, accountID, payment, time);
}
