#include "Meter.h"
#include <iostream>

Meter::Meter() {
    meterId = 0;
    customerId = 0;
    location = "";
}

Meter::Meter(int mId, int cId, string loc) {
    setMeterId(mId);
    setCustomerId(cId);
    setLocation(loc);
}

Meter::~Meter() {
}

int Meter::getMeterId() { return meterId; }
int Meter::getCustomerId() { return customerId; }
string Meter::getLocation() { return location; }

void Meter::setMeterId(int id) {
    if (id <= 0) {
        throw "Meter ID must be more than 0";
    }
    meterId = id;
}

void Meter::setCustomerId(int id) {
    if (id <= 0) {
        throw "Customer ID must be more than 0";
    }
    customerId = id;
}

void Meter::setLocation(string loc) {
    if (loc == "") {
        throw "Location cannot be empty";
    }
    location = loc;
}

void Meter::display() {
    cout << "Meter ID: " << meterId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Location: " << location << endl;
}
