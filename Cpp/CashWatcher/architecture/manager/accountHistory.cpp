#include "accountHistory.h"

AccountHistory::AccountHistory():
    amountRecords(0)
{
}

void AccountHistory::addRecord(const AccountOperation &operation)
{
    // add sorting by time addition
    listOfOperations.push_back(operation);
    amountRecords++;
}

void AccountHistory::clear()
{
    listOfOperations.clear();
    amountRecords = 0;
}

void AccountHistory::sortByTime()
{
    //
}

std::ostream &operator << (std::ostream &output, const AccountHistory &history)
{
    output << history.amountRecords << endl;
    for (int i = 0; i < history.amountRecords; ++i)
    {
        output << history.listOfOperations[i] << endl;
    }
    return output;
}

std::istream &operator >> (std::istream &input, AccountHistory &history)
{
    input >> history.amountRecords;
    for (int i = 0; i < history.amountRecords; ++i)
    {
        AccountOperation operation;
        input >> operation;
        history.listOfOperations[i] = operation;
    }
    return input;
}

int AccountHistory::getAmountRecords() const
{
    return amountRecords;
}

const AccountOperation &AccountHistory::operator [](const int index) const
{
    return listOfOperations[index];
}

void AccountHistory::print() const
{
    cout << "History:\n";
    for (int i = 0; i < amountRecords; ++i)
    {
        cout << i + 1 << ") ";
        printAccountOperation(listOfOperations[i]);
        cout << endl;
    }
}
