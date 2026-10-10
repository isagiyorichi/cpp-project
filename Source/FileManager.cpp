#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

FileManager::FileManager() {
}

FileManager::~FileManager() {
}

// Cut a line at every | sign and put the pieces in the parts array.
// It returns how many pieces were found.
int FileManager::splitLine(string line, string parts[], int maxParts) {
    int n = 0;
    string piece = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '|') {
            if (n < maxParts) {
                parts[n] = piece;
            }
            n++;
            piece = "";
        } else {
            piece = piece + line[i];
        }
    }
    if (n < maxParts) {
        parts[n] = piece;
    }
    n++;
    return n;
}

// Count the lines in a file (0 if the file does not exist)
int FileManager::countLines(string fileName) {
    ifstream file(fileName.c_str());
    int count = 0;
    string line;
    if (!file) {
        return 0;
    }
    while (getline(file, line)) {
        count++;
    }
    file.close();
    return count;
}

// ---------- SAVE ----------

void FileManager::saveCustomers(string fileName, Customer* list, int count) {
    ofstream file(fileName.c_str());
    if (!file) {
        throw "Cannot open the customers file for saving";
    }
    for (int i = 0; i < count; i++) {
        file << list[i].getCustomerId() << "|"
             << list[i].getName() << "|"
             << list[i].getAddress() << "|"
             << list[i].getPhone() << "|"
             << list[i].getPlanType() << endl;
    }
    file.close();
}

void FileManager::saveMeters(string fileName, Meter* list, int count) {
    ofstream file(fileName.c_str());
    if (!file) {
        throw "Cannot open the meters file for saving";
    }
    for (int i = 0; i < count; i++) {
        file << list[i].getMeterId() << "|"
             << list[i].getCustomerId() << "|"
             << list[i].getLocation() << endl;
    }
    file.close();
}

void FileManager::saveReadings(string fileName, Reading* list, int count) {
    ofstream file(fileName.c_str());
    if (!file) {
        throw "Cannot open the readings file for saving";
    }
    for (int i = 0; i < count; i++) {
        file << list[i].getMeterId() << "|"
             << list[i].getMonth() << "|"
             << list[i].getYear() << "|"
             << list[i].getPreviousReading() << "|"
             << list[i].getCurrentReading() << endl;
    }
    file.close();
}

void FileManager::saveBills(string fileName, Bill* list, int count) {
    ofstream file(fileName.c_str());
    if (!file) {
        throw "Cannot open the bills file for saving";
    }
    file << fixed << setprecision(2);     // show money with 2 digits after the point
    for (int i = 0; i < count; i++) {
        file << list[i].getBillId() << "|"
             << list[i].getCustomerId() << "|"
             << list[i].getMeterId() << "|"
             << list[i].getMonth() << "|"
             << list[i].getYear() << "|"
             << list[i].getUnits() << "|"
             << list[i].getAmount() << "|";
        if (list[i].getIsPaid()) {
            file << 1 << endl;
        } else {
            file << 0 << endl;
        }
    }
    file.close();
}

// ---------- LOAD ----------

int FileManager::loadCustomers(string fileName, Customer* list, int maxCount) {
    ifstream file(fileName.c_str());
    int count = 0;
    string line;
    string parts[5];
    if (!file) {
        return 0;      // file not found, so there is nothing to load
    }
    while (count < maxCount && getline(file, line)) {
        if (line == "") {
            continue;
        }
        if (splitLine(line, parts, 5) != 5) {
            cout << "Skipped a bad line in " << fileName << endl;
            continue;
        }
        try {
            list[count] = Customer(stoi(parts[0]), parts[1], parts[2], parts[3], stoi(parts[4]));
            count++;
        } catch (...) {
            cout << "Skipped a bad line in " << fileName << endl;
        }
    }
    file.close();
    return count;
}

int FileManager::loadMeters(string fileName, Meter* list, int maxCount) {
    ifstream file(fileName.c_str());
    int count = 0;
    string line;
    string parts[3];
    if (!file) {
        return 0;
    }
    while (count < maxCount && getline(file, line)) {
        if (line == "") {
            continue;
        }
        if (splitLine(line, parts, 3) != 3) {
            cout << "Skipped a bad line in " << fileName << endl;
            continue;
        }
        try {
            list[count] = Meter(stoi(parts[0]), stoi(parts[1]), parts[2]);
            count++;
        } catch (...) {
            cout << "Skipped a bad line in " << fileName << endl;
        }
    }
    file.close();
    return count;
}

int FileManager::loadReadings(string fileName, Reading* list, int maxCount) {
    ifstream file(fileName.c_str());
    int count = 0;
    string line;
    string parts[5];
    if (!file) {
        return 0;
    }
    while (count < maxCount && getline(file, line)) {
        if (line == "") {
            continue;
        }
        if (splitLine(line, parts, 5) != 5) {
            cout << "Skipped a bad line in " << fileName << endl;
            continue;
        }
        try {
            list[count] = Reading(stoi(parts[0]), stoi(parts[1]), stoi(parts[2]), stoi(parts[3]), stoi(parts[4]));
            count++;
        } catch (...) {
            cout << "Skipped a bad line in " << fileName << endl;
        }
    }
    file.close();
    return count;
}

int FileManager::loadBills(string fileName, Bill* list, int maxCount) {
    ifstream file(fileName.c_str());
    int count = 0;
    string line;
    string parts[8];
    if (!file) {
        return 0;
    }
    while (count < maxCount && getline(file, line)) {
        if (line == "") {
            continue;
        }
        if (splitLine(line, parts, 8) != 8) {
            cout << "Skipped a bad line in " << fileName << endl;
            continue;
        }
        try {
            Bill b(stoi(parts[0]), stoi(parts[1]), stoi(parts[2]), stoi(parts[3]), stoi(parts[4]), stoi(parts[5]));
            b.setAmount(stod(parts[6]));
            b.setIsPaid(parts[7] == "1");
            list[count] = b;
            count++;
        } catch (...) {
            cout << "Skipped a bad line in " << fileName << endl;
        }
    }
    file.close();
    return count;
}
