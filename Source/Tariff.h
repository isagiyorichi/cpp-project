#ifndef TARIFF_H
#define TARIFF_H

#include <string>
using namespace std;

// Tariff means "price plan".
// This is the parent class. Home and Shop plans are made from it.
class Tariff {
protected:
    string planName;    // name of the plan
    double fixedFee;    // fee we pay every month

public:
    Tariff();                      // constructor with no values
    Tariff(string name, double fee);   // constructor with values
    virtual ~Tariff();             // destructor

    string getPlanName();
    double getFixedFee();

    // "virtual" means: each child plan can have its own version
    virtual double calculateAmount(int units);
};

// Plan for houses (child of Tariff)
class HomeTariff : public Tariff {
public:
    HomeTariff();
    double calculateAmount(int units);
};

// Plan for shops (child of Tariff)
class ShopTariff : public Tariff {
public:
    ShopTariff();
    double calculateAmount(int units);
};

#endif
