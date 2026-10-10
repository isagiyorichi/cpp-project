#ifndef METER_H
#define METER_H

#include <string>
using namespace std;

// Meter = the machine that counts electricity units
class Meter {
private:
    int meterId;
    int customerId;       // which customer owns this meter
    string location;      // where the meter is fixed

public:
    Meter();
    Meter(int mId, int cId, string loc);
    ~Meter();

    int getMeterId();
    int getCustomerId();
    string getLocation();

    void setMeterId(int id);
    void setCustomerId(int id);
    void setLocation(string loc);

    void display();
};

#endif
