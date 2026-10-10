#ifndef READING_H
#define READING_H

using namespace std;

// Reading = the meter numbers noted down for one month
class Reading {
private:
    int meterId;
    int month;
    int year;
    int previousReading;   // number shown on the meter last month
    int currentReading;    // number shown on the meter this month

public:
    Reading();
    Reading(int mId, int m, int y, int prev, int curr);
    ~Reading();

    int getMeterId();
    int getMonth();
    int getYear();
    int getPreviousReading();
    int getCurrentReading();

    void setMeterId(int id);
    void setMonth(int m);
    void setYear(int y);
    void setPreviousReading(int prev);
    void setCurrentReading(int curr);

    int getUnitsUsed();    // current reading minus previous reading
    void display();
};

#endif
