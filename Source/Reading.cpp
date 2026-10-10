#include "Reading.h"
#include <iostream>

Reading::Reading() {
    meterId = 0;
    month = 1;
    year = 2026;
    previousReading = 0;
    currentReading = 0;
}

Reading::Reading(int mId, int m, int y, int prev, int curr) {
    setMeterId(mId);
    setMonth(m);
    setYear(y);
    setPreviousReading(prev);
    setCurrentReading(curr);    // this one must come after the previous reading
}

Reading::~Reading() {
}

int Reading::getMeterId() { return meterId; }
int Reading::getMonth() { return month; }
int Reading::getYear() { return year; }
int Reading::getPreviousReading() { return previousReading; }
int Reading::getCurrentReading() { return currentReading; }

void Reading::setMeterId(int id) {
    if (id <= 0) {
        throw "Meter ID must be more than 0";
    }
    meterId = id;
}

void Reading::setMonth(int m) {
    if (m < 1 || m > 12) {
        throw "Month must be between 1 and 12";
    }
    month = m;
}

void Reading::setYear(int y) {
    if (y < 2000 || y > 2100) {
        throw "Year must be between 2000 and 2100";
    }
    year = y;
}

void Reading::setPreviousReading(int prev) {
    if (prev < 0) {
        throw "Reading cannot be negative";
    }
    previousReading = prev;
}

void Reading::setCurrentReading(int curr) {
    if (curr < previousReading) {
        throw "Current reading cannot be less than previous reading";
    }
    currentReading = curr;
}

int Reading::getUnitsUsed() {
    return currentReading - previousReading;
}

void Reading::display() {
    cout << "Meter ID: " << meterId << endl;
    cout << "Month/Year: " << month << "/" << year << endl;
    cout << "Previous reading: " << previousReading << endl;
    cout << "Current reading: " << currentReading << endl;
    cout << "Units used: " << getUnitsUsed() << endl;
}
