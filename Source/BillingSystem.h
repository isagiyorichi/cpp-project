#ifndef BILLINGSYSTEM_H
#define BILLINGSYSTEM_H

#include <string>
#include "Customer.h"
#include "Meter.h"
#include "Reading.h"
#include "Bill.h"
#include "Tariff.h"
#include "FileManager.h"
using namespace std;

// BillingSystem = the main class. It keeps all records and does all the work.
// The records are kept in dynamic arrays (made with new, freed with delete[]).
class BillingSystem {
private:
    Customer* customers;
    int customerCount;       // how many customers are stored
    int customerCapacity;    // how many customers the array can hold

    Meter* meters;
    int meterCount;
    int meterCapacity;

    Reading* readings;
    int readingCount;
    int readingCapacity;

    Bill* bills;
    int billCount;
    int billCapacity;

    FileManager fileManager;

    // small helper functions
    string askText(string message);
    int findCustomer(int id);       // returns position in array, or -1 if not found
    int findMeter(int id);
    int findReading(int meterId, int month, int year);
    int findBill(int billId);
    int findBillOfMeter(int meterId, int month, int year);
    int nextBillId();

    // make an array bigger when it is full
    void growCustomers();
    void growMeters();
    void growReadings();
    void growBills();

    void addCustomer();
    void addMeter();
    void addReading();

    void searchCustomer();
    void updateCustomer();
    void deleteCustomer();
    void deleteMeter();
    void deleteReading();

    void generateBill();
    void payBill();

public:
    BillingSystem();
    ~BillingSystem();

    int askNumber(string message);

    void showMenu();
    void addRecord();
    void displayRecords();
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void mainTransaction();
    void showReport();
    void saveLoadMenu();
    void saveData();
    void loadData();
};

#endif
