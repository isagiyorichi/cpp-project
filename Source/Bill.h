#ifndef BILL_H
#define BILL_H

#include "Tariff.h"
using namespace std;

// Bill = the amount a customer has to pay for one month
class Bill {
private:
    int billId;
    int customerId;
    int meterId;
    int month;
    int year;
    int units;         // units of electricity used
    double amount;     // money to pay
    bool isPaid;       // true = paid, false = not paid

public:
    Bill();
    Bill(int bId, int cId, int mId, int m, int y, int u);
    ~Bill();

    int getBillId();
    int getCustomerId();
    int getMeterId();
    int getMonth();
    int getYear();
    int getUnits();
    double getAmount();
    bool getIsPaid();

    void setAmount(double a);
    void setIsPaid(bool paid);

    // The plan can be Home or Shop, so we use a Tariff pointer.
    // The program picks the right plan while running (polymorphism).
    void calculateAmount(Tariff* plan);

    void markAsPaid();
    void display();
};

#endif
