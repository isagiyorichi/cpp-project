#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "Customer.h"
#include "Meter.h"
#include "Reading.h"
#include "Bill.h"
using namespace std;

// FileManager = saves records to files and loads them back.
// Each record is one line. The parts are separated by the | sign.
class FileManager {
private:
    // cuts one line into parts at every | sign
    int splitLine(string line, string parts[], int maxParts);

public:
    FileManager();
    ~FileManager();

    int countLines(string fileName);

    void saveCustomers(string fileName, Customer* list, int count);
    void saveMeters(string fileName, Meter* list, int count);
    void saveReadings(string fileName, Reading* list, int count);
    void saveBills(string fileName, Bill* list, int count);

    // load functions return how many records were read
    int loadCustomers(string fileName, Customer* list, int maxCount);
    int loadMeters(string fileName, Meter* list, int maxCount);
    int loadReadings(string fileName, Reading* list, int maxCount);
    int loadBills(string fileName, Bill* list, int maxCount);
};

#endif
