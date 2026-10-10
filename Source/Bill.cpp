#include "Bill.h"
#include <iostream>

Bill::Bill() {
    billId = 0;
    customerId = 0;
    meterId = 0;
    month = 1;
    year = 2026;
    units = 0;
    amount = 0;
    isPaid = false;
}

Bill::Bill(int bId, int cId, int mId, int m, int y, int u) {
    if (bId <= 0 || cId <= 0 || mId <= 0) {
        throw "IDs must be more than 0";
    }
    if (m < 1 || m > 12) {
        throw "Month must be between 1 and 12";
    }
    if (u < 0) {
        throw "Units cannot be negative";
    }
    billId = bId;
    customerId = cId;
    meterId = mId;
    month = m;
    year = y;
    units = u;
    amount = 0;
    isPaid = false;
}

Bill::~Bill() {
}

int Bill::getBillId() { return billId; }
int Bill::getCustomerId() { return customerId; }
int Bill::getMeterId() { return meterId; }
int Bill::getMonth() { return month; }
int Bill::getYear() { return year; }
int Bill::getUnits() { return units; }
double Bill::getAmount() { return amount; }
bool Bill::getIsPaid() { return isPaid; }

void Bill::setAmount(double a) {
    if (a < 0) {
        throw "Amount cannot be negative";
    }
    amount = a;
}

void Bill::setIsPaid(bool paid) {
    isPaid = paid;
}

// Ask the plan (Home or Shop) how much to charge for these units
void Bill::calculateAmount(Tariff* plan) {
    amount = plan->calculateAmount(units);
}

void Bill::markAsPaid() {
    isPaid = true;
}

void Bill::display() {
    cout << "Bill ID: " << billId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Meter ID: " << meterId << endl;
    cout << "Month/Year: " << month << "/" << year << endl;
    cout << "Units used: " << units << endl;
    cout << "Amount: " << amount << endl;
    if (isPaid) {
        cout << "Status: Paid" << endl;
    } else {
        cout << "Status: Unpaid" << endl;
    }
}
