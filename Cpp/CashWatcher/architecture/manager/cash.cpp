#include "cash.h"

Cash::Cash():
    cash(0.0)
{
}

Cash::Cash(const double amount):
    cash(toMoney(amount))
{
}

double Cash::peekCash() const
{
    return cash;
}

void Cash::depositCash(const double deposit)
{
    cash += toMoney(deposit);
}

void Cash::payoutCash(const double payout)
{
    cash -= toMoney(payout);
}

void Cash::set(const double amount)
{
    cash = amount;
}

double Cash::toMoney(const double amount)
{
    return (ceil(100.0 * abs(amount))) / 100.0;
}

std::ostream &operator <<(std::ostream &out, const Cash &someCash)
{
    out.precision(2);
    out << fixed << someCash.cash;
    return out;
}

std::istream &operator >>(std::istream &in, Cash &someCash)
{
    in >> someCash.cash;
    return in;
}

void Cash::print() const
{
    std::cout.precision(2);
    cout << "cash(" << fixed << cash << ")\n";
}
