#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "architecture/auxiliary/time.h"
#include "cash.h"
#include "accountOperation.h"
#include "accountDescription.h"
#include "accountHistory.h"

class Account
{
public:
    Account(const int accountID = AccountOperation::zeroID,
            const std::string accountName = "unnamed",
            const double startValue = 0.0,
            const Time &createTime = Time::getNow());
    ~Account();

    int getID() const;
    double peekCash() const;
    void makeOperation(const AccountOperation &operation);
    const AccountDescription *getAccountDescription() const;

    friend std::ostream &operator <<(std::ostream &output, const Account &account);
    friend std::istream &operator >>(std::istream &input, Account &account);

    void print() const;
private:
    double sessionBalance;
    double alltimeBalance;
    Cash *cash;
    AccountDescription *description;
    AccountHistory *history;
};

#endif // ACCOUNT_H
