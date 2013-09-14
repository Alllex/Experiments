#ifndef CASH_H
#define CASH_H

#include <iostream>
#include <cmath>
using namespace std;

class Cash
{
public:
    Cash();
    Cash(const double amount);

    double peekCash() const;                    //return current value of cash
    void depositCash(const double deposit);     //add some cash to current value
    void payoutCash(const double payout);       //take some cash from current value
    void set(const double amount);

    static double toMoney(const double amount);              //translate double to money format, like "1056.14"

    friend ostream &operator << (ostream &out, const Cash &someCash);
    friend istream &operator >> (istream &in, Cash &someCash);

    void print() const;
private:
    double cash;
};

#endif // CASH_H
