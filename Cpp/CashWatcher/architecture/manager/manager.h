#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
using namespace std;

#include "architecture/auxiliary/time.h"
#include "account.h"

class Manager
{
public:
    Manager(const std::string &newUserName = "user");
    ~Manager();

    int createAccount(const string &accountName,
                      const double startValue,
                      const Time &time);  //return ID of new account

    void destroyAccount(const int accountID);

    int getAmountAccounts() const;
    double peekCash(const int accountID);
    void makeOperation(const TypeOfOperation opType = AccountOperation::defaultOperation,
                       const int accountID = AccountOperation::zeroID,
                       const double payment = AccountOperation::defaultPayment,
                       const Time &time = Time::getNow());

    void saveLogsToFile() const;
    void loadLogsFromFile();

    void printLogs() const;
    void clearAccounts();

    vector<int> ID;
private:
    static const char *logFileName;
    static const char *logFolderName;

    std::string userName;
    int amountAccounts;
    vector<Account*> account;

    int findAccountIndex(const int accountID);
    int getNextID() const;

    bool createLogFolder() const;
    bool createLogFile() const;

    std::string getLogFilePath() const;
};

#endif // MANAGER_H
