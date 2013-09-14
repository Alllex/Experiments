#include "manager.h"

const char *Manager::logFileName = "accounts.log";
const char *Manager::logFolderName = "logs";

Manager::Manager(const std::string &newUserName):
    amountAccounts(0)
{
    userName = newUserName;
}

Manager::~Manager()
{
    clearAccounts();
}

int Manager::createAccount(const std::string &accountName, const double startValue, const Time &time)
{
    const int newID = getNextID();
    Account *newAccount = new Account(newID, accountName, startValue, time);
    account.push_back(newAccount);
    amountAccounts++;
    ID.push_back(newID);
    return newID;
}

void Manager::destroyAccount(const int accountID)
{
    int accountIndex = findAccountIndex(accountID);
    if (accountIndex < 0)
    {
        return;
    }
    delete account[accountIndex];
    ID.erase(ID.begin() + accountIndex);
    account.erase(account.begin() + accountIndex);
    amountAccounts--;
}

int Manager::getAmountAccounts() const
{
    return amountAccounts;
}

void Manager::makeOperation(const TypeOfOperation opType,
                            const int accountID,
                            const double payment,
                            const Time &time)
{
    int accountIndex = findAccountIndex(accountID);
    if (accountIndex < 0)
    {
        return;
    }
    account[accountIndex]->makeOperation(AccountOperation(opType, accountID, payment, time));
}

void Manager::saveLogsToFile() const
{
    createLogFolder();
    ofstream output(getLogFilePath().c_str(), fstream::out);
    output << amountAccounts << endl << endl;
    for (int i = 0; i < amountAccounts; ++i)
    {
        output << (*account[i]) << endl;
    }
    output.close();
}

void Manager::loadLogsFromFile()
{
    ifstream input;
    input.open(getLogFilePath().c_str());
    input >> amountAccounts;
    for (int i = 0; i < amountAccounts; ++i)
    {
        Account *tempAccount = new Account;
        input >> (*tempAccount);
        account.push_back(tempAccount);
        ID.push_back(tempAccount->getID());
    }
    if (input.is_open())
    {
        input.close();
    }
}

void Manager::printLogs() const
{
    cout << "Manager logs:\n";
    cout << "User name: \"" << userName << "\"\n";
    cout << "Accounts (" << amountAccounts << "):\n";
    for (int i = 0; i < amountAccounts; ++i)
    {
        cout << "------------------------------\n";
        cout << i + 1 << ") ";
        account[i]->print();
        cout << "------------------------------\n";
    }
}

void Manager::clearAccounts()
{
    for (int i = 0; i < amountAccounts; ++i)
    {
        delete account[i];
    }
    account.clear();
    amountAccounts = 0;
}

int Manager::findAccountIndex(const int accountID)
{
    for (int i = 0; i < amountAccounts; ++i)
    {
        if (accountID == account[i]->getID())
        {
            return i;
        }
    }
    return -1;
}

int Manager::getNextID() const
{
    int nextID = AccountOperation::zeroID;
    for (int i = 0; i < amountAccounts; ++i)
    {
        if (nextID < account[i]->getID())
        {
            nextID = account[i]->getID();
        }
    }
    return nextID + 1;
}

bool Manager::createLogFolder() const
{
#ifdef __linux__
    std::string logFolderPath = logFolderName;
    logFolderPath += "/";
    logFolderPath += userName;
    std::string command = "mkdir -p " + logFolderPath;
    int result = system(command.c_str());
    if (result)
    {
        return false;
    }
#else
#ifdef __WIN32__

#else
    return false;
#endif
#endif
    return true;
}

bool Manager::createLogFile() const
{
    createLogFolder();
#ifdef __linux__
    ofstream file;
    file.open(getLogFilePath().c_str());
    if (!file.is_open())
    {
        return false;
    }
    file.close();
#else
#ifdef __WIN32__

#else
    return false;
#endif
#endif
    return true;

}

std:: string Manager::getLogFilePath() const
{
    std::string logFilePath = logFolderName;
    logFilePath += "/";
    logFilePath += userName;
    logFilePath += "/";
    logFilePath += logFileName;
    return logFilePath;
}

double Manager::peekCash(const int accountID)
{
    int accountIndex = findAccountIndex(accountID);
    if (accountIndex < 0)
    {
        return 0.0;
    }
    return account[accountIndex]->peekCash();
}


