#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

// Customer = a person who uses electricity
class Customer {
private:                  // private = hidden from outside (encapsulation)
    int customerId;
    string name;
    string address;
    string phone;
    int planType;         // 1 = Home plan, 2 = Shop plan

public:
    Customer();                                              // empty constructor
    Customer(int id, string n, string a, string p, int type);  // constructor with values
    ~Customer();                                             // destructor

    // get = read the value, set = change the value (with checks)
    int getCustomerId();
    string getName();
    string getAddress();
    string getPhone();
    int getPlanType();

    void setCustomerId(int id);
    void setName(string n);
    void setAddress(string a);
    void setPhone(string p);
    void setPlanType(int type);

    void display();       // show the customer on screen
};

#endif
