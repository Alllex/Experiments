#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "architecture/auxiliary/time.h"
#include "architecture/manager/cash.h"
#include "architecture/manager/accountOperation.h"
#include "architecture/manager/accountDescription.h"
#include "architecture/manager/accountHistory.h"
#include "architecture/manager/account.h"
#include "architecture/manager/manager.h"
#include "architecture/user.h"


class Tester
{
public:
    void run();
private:
    void timeTest();
    void cashTest();
    void accountDescriptionTest();
    void accountHisoryTest();
    void accountTest();
    void managerTest();
    void marketTest();
    void userTest();

};

#endif // TESTER_H
