#include "accountOperation.h"

void printAccountOperation(const AccountOperation &operation)
{
    cout.precision(2);
    cout << "Operation("
         << (operation.opType == opDeposit ? "Deposit to  #" : "Payout from #")
         << operation.accountID << " ["
         << fixed << operation.payment << "$] at ";
    operation.time.print();
    cout << ")";
}

ostream &operator << (ostream &output, const AccountOperation &operation)
{
    output.precision(2);
    output << operation.opType << endl
           << operation.accountID << endl
           << fixed << operation.payment << endl
           << operation.time;
    return output;
}

istream &operator >> (istream &input, AccountOperation &operation)
{
    int operationType = 0;
    input >> operationType
          >> operation.accountID
          >> operation.payment
          >> operation.time;
    operation.opType = static_cast<TypeOfOperation> (operationType);
    return input;
}
