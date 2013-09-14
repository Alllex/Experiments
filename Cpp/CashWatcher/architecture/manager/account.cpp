#include "account.h"

Account::Account(const int accountID, const string accountName, const double startValue, const Time &createTime):
    sessionBalance(0.0),
    alltimeBalance(0.0)
{
    cash = new Cash(startValue);
    description = new AccountDescription(accountID, accountName, createTime);
    history = new AccountHistory();
}

Account::~Account()
{
    delete cash;
    delete description;
    delete history;
}

int Account::getID() const
{
    return description->getID();
}

double Account::peekCash() const
{
    return cash->peekCash();
}

void Account::makeOperation(const AccountOperation &operation)
{
    double payment = Cash::toMoney(operation.payment);
    if (operation.opType == opDeposit)
    {
        sessionBalance += payment;
        alltimeBalance += payment;
        cash->depositCash(payment);
    }
    else if (operation.opType == opPayout)
    {
        sessionBalance -= payment;
        alltimeBalance -= payment;
        cash->payoutCash(payment);
    }
    history->addRecord(operation);
}

const AccountDescription *Account::getAccountDescription() const
{
    return description;
}

std::ostream &operator <<(std::ostream &output, const Account &account)
{
    output << (*account.description) << endl
           << (*account.cash) << endl
           << account.alltimeBalance << endl
           << (*account.history);
    return output;
}

std::istream &operator >>(std::istream &input, Account &account)
{
    input  >> (*account.description)
           >> (*account.cash)
           >> account.alltimeBalance
           >> (*account.history);
    return input;
}

void Account::print() const
{
    cout << "Account:\n";
    description->print();
    cash->print();
    cout.precision(2);
    cout << "Alltime balance (" << fixed << alltimeBalance << ")\n";
    history->print();
}



