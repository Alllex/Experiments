#include "tester.h"

void Tester::run()
{
    //timeTest();
    //cashTest();
    //accountDescriptionTest();
    //accountHisoryTest();
    //accountTest();
    managerTest();
}

void Tester::timeTest()
{
    cout << "Time test:\n";
    Time time = Time::getNow();
    time.print();

    ofstream output;
    output.open("tests/time");
    time.set(1994, 9, 16, 0, 0);
    output << time << endl;
    time = Time::getNow();
    output << time << endl;
    output.close();

    ifstream input;
    input.open("tests/time");
    Time time1;
    Time time2;
    input >> time1 >> time2;
    cout << "Time1 ";
    time1.print();
    cout << "Time2 ";
    time2.print();
    cout.precision(3);
    cout << "Time difference: (time2 - time1) = " << fixed << (time2 - time1) << " days\n";
    input.close();
}

void Tester::cashTest()
{
    cout.precision(2);
    cout << "Cash test:\n";
    Cash cash(100);
    cash.print();
    cout << "Peek cash: " << cash << endl;
    cout << "deposit " << fixed << cash.peekCash() << " to cash\n";
    cash.depositCash(cash.peekCash());
    cash.print();
    cout << "payout " << fixed << cash.peekCash() / 3 << " from cash\n";
    cash.payoutCash(cash.peekCash() / 3);
    cash.print();

    ofstream output;
    output.open("tests/cash");
    Cash cash1(1000);
    Cash cash2(500);
    cout << "\nCash1: ";
    cash1.print();
    cout << "Cash2: ";
    cash2.print();
    cout << "deposit " << fixed << cash2.peekCash() << " to cash1\n";
    cash1.depositCash(cash2.peekCash());
    cash1.print();
    const double payment = 166.67;
    cout << "payout " << fixed << payment << " from cash2\n";
    cash2.payoutCash(payment);
    cash2.print();
    cout << "save to file\n";
    output << cash1 << endl << cash2;
    output.close();

    cash1.set(0);
    cash2.set(0);
    ifstream input;
    input.open("tests/cash");
    input >> cash1 >> cash2;
    cout << "Cash1: ";
    cash1.print();
    cout << "Cash2: ";
    cash2.print();
    input.close();
}

void Tester::accountDescriptionTest()
{
    AccountDescription info(1001, "visa junior", Time(2012, 12, 1, 9, 0));
    info.print();

    ofstream output;
    output.open("tests/accountDescription");
    cout << "Save to file\n";
    output << info << endl;
    output.close();

    info = AccountDescription();
    cout << "Cleared info:\n";
    info.print();
    ifstream input;
    input.open("tests/accountDescription");
    input >> info;
    cout << "Info has read\n";
    cout << info << endl;
    info.print();
    input.close();
}

void Tester::accountHisoryTest()
{
    AccountHistory history;
    history.addRecord(AccountOperation(opDeposit, 1001, 102.50));
    history.addRecord(AccountOperation(opDeposit, 1357, 357.598));
    history.addRecord(AccountOperation(opPayout, 1001, 102));
    history.print();

    cout << "Save to file\n";
    ofstream output;
    output.open("tests/accountHistory");
    if (output.is_open())
    {
        output << history << endl;
    }
    else
    {
        cout << "Bad file\n";
    }
    output.close();

    history.clear();
    cout << "Reading history...\n";
    ifstream input;
    input.open("tests/accountHistory");
    if (input.is_open())
    {
        input >> history;
        cout << "History has read\n";
        history.print();
    }
    else
    {
        cout << "Bad input file\n";
    }
    input.close();
}

void Tester::accountTest()
{
    Account account(1001, "visa junior", 1000);
    account.makeOperation(AccountOperation(opDeposit, 1001, 102.50));
    account.makeOperation(AccountOperation(opDeposit, 1001, 357.598));
    account.makeOperation(AccountOperation(opPayout, 1001, 101));
    account.print();

    const AccountDescription *info = account.getAccountDescription();
    info->print();
}

void Tester::managerTest()
{
    Manager man("alllex");
    man.loadLogsFromFile();
    //man.createAccount("first", 100, Time::getNow());
//    man.createAccount("second", 200, Time::getNow());
//    man.createAccount("third", 300, Time::getNow());
//    //man.printLogs();
//    for (int i = 0; i < man.getAmountAccounts(); ++i)
//    {
//        int id = man.ID[i];
//        man.makeOperation(opDeposit, id, 1000);
//    }
//    for (int i = 0; i < man.getAmountAccounts(); ++i)
//    {
//        int id = man.ID[i];
//        man.makeOperation(opPayout, id, 1);
//    }
    man.printLogs();
    man.saveLogsToFile();
}


















