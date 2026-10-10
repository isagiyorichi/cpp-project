#include "Customer.h"
#include <iostream>

Customer::Customer() {
    customerId = 0;
    name = "";
    address = "";
    phone = "";
    planType = 1;
}

Customer::Customer(int id, string n, string a, string p, int type) {
    setCustomerId(id);
    setName(n);
    setAddress(a);
    setPhone(p);
    setPlanType(type);
}

Customer::~Customer() {
}

int Customer::getCustomerId() { return customerId; }
string Customer::getName() { return name; }
string Customer::getAddress() { return address; }
string Customer::getPhone() { return phone; }
int Customer::getPlanType() { return planType; }

// Each set function checks the value first (validation)
void Customer::setCustomerId(int id) {
    if (id <= 0) {
        throw "Customer ID must be more than 0";
    }
    customerId = id;
}

void Customer::setName(string n) {
    if (n == "") {
        throw "Name cannot be empty";
    }
    name = n;
}

void Customer::setAddress(string a) {
    if (a == "") {
        throw "Address cannot be empty";
    }
    address = a;
}

void Customer::setPhone(string p) {
    // phone must have exactly 10 digits
    if (p.length() != 10) {
        throw "Phone must have exactly 10 digits";
    }
    for (int i = 0; i < 10; i++) {
        if (p[i] < '0' || p[i] > '9') {
            throw "Phone must have exactly 10 digits";
        }
    }
    phone = p;
}

void Customer::setPlanType(int type) {
    if (type != 1 && type != 2) {
        throw "Plan type must be 1 (Home) or 2 (Shop)";
    }
    planType = type;
}

void Customer::display() {
    cout << "Customer ID: " << customerId << endl;
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
    if (planType == 1) {
        cout << "Plan: Home" << endl;
    } else {
        cout << "Plan: Shop" << endl;
    }
}
