#ifndef ACCOUNTHISTORY_H
#define ACCOUNTHISTORY_H

#include <iostream>
#include <vector>
using namespace std;

#include "architecture/auxiliary/time.h"
#include "accountOperation.h"

class AccountHistory
{
public:
    AccountHistory();

    void addRecord(const AccountOperation &operation);
    void clear();
    void sortByTime();

    friend std::ostream &operator << (std::ostream &output, const AccountHistory &history);
    friend std::istream &operator >> (std::istream &input, AccountHistory &history);

    int getAmountRecords() const;
    const AccountOperation &operator [] (const int index) const;

    void print() const;
private:
    int amountRecords;
    vector<AccountOperation> listOfOperations;
};

#endif // ACCOUNTHISTORY_H
