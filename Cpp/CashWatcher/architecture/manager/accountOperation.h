#ifndef ACCOUNTOPERATION_H
#define ACCOUNTOPERATION_H

#include <iostream>
using namespace std;

#include "architecture/auxiliary/time.h"
#include "cash.h"

enum TypeOfOperation
{
    opDeposit,
    opPayout
};

struct AccountOperation
{
    static const int zeroID = 1000;
    static const TypeOfOperation defaultOperation = opDeposit;
    static const double defaultPayment = 0.0;
    TypeOfOperation opType;
    int accountID;
    double payment;
    Time time;

    AccountOperation(const TypeOfOperation setOpType = defaultOperation,
                     const int setAccountID = zeroID,
                     const double setPayment = defaultPayment,
                     const Time setTime = Time::getNow()):
        opType(setOpType),
        accountID(setAccountID),
        payment(Cash::toMoney(setPayment)),
        time(setTime)
    {}

    AccountOperation(const AccountOperation &operation):
        opType(operation.opType),
        accountID(operation.accountID),
        payment(operation.payment),
        time(operation.time)
    {}


    friend std::ostream &operator << (std::ostream &output, const AccountOperation &operation);
    friend std::istream &operator >> (std::istream &input, AccountOperation &operation);
};

void printAccountOperation(const AccountOperation &operation);

#endif // ACCOUNTOPERATION_H
