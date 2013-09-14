#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "auxiliary/time.h"
#include "manager/manager.h"

class User
{
public:
    User(const string newUserName = "user");
    ~User();

    // user settings
    void changeUserName(const std::string &newUserName);

    // manager functions
    double peekCash(const int accountID) const;
    void depositCash(const int accountID, const double payment, const Time &time);
    void payoutCash(const int accountID, const double payment, const Time &time);

    // market functions
//    void addPurchase(const TypeOfPurchase type,
//                     const CategoryOfProduct category,
//                     const std::string &name,
//                     const std::string &sort,
//                     const std::string &shop,
//                     const double cost,
//                     const double price,
//                     const double amount,
//                     const UnitsOfAmount units,
//                     const Time time);

    // access functions
    //const PurchaseArchive *getArchive() const;
private:
    std::string userName;
    std::string userPass;
    Time timeCreate;

    Manager *manager;
};

#endif // USER_H
