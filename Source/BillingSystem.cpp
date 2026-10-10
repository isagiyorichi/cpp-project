#include "BillingSystem.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// ---------- Start and finish ----------

// Constructor: make the arrays (dynamic memory)
BillingSystem::BillingSystem() {
    customerCapacity = 10;
    customers = new Customer[customerCapacity];
    customerCount = 0;

    meterCapacity = 10;
    meters = new Meter[meterCapacity];
    meterCount = 0;

    readingCapacity = 10;
    readings = new Reading[readingCapacity];
    readingCount = 0;

    billCapacity = 10;
    bills = new Bill[billCapacity];
    billCount = 0;
}

// Destructor: give the memory back
BillingSystem::~BillingSystem() {
    delete[] customers;
    delete[] meters;
    delete[] readings;
    delete[] bills;
}

// ---------- Helper functions ----------

// Ask for a whole number. Keep asking until the user types a proper number.
int BillingSystem::askNumber(string message) {
    string line;
    while (true) {
        cout << message;
        if (!getline(cin, line)) {
            exit(0);        // input has ended, so stop the program
        }
        try {
            size_t used;
            int value = stoi(line, &used);
            if (used == line.length()) {
                return value;
            }
        } catch (...) {
        }
        cout << "Please type a number." << endl;
    }
}

// Ask for a line of text
string BillingSystem::askText(string message) {
    string line;
    cout << message;
    if (!getline(cin, line)) {
        exit(0);
    }
    return line;
}

int BillingSystem::findCustomer(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].getCustomerId() == id) {
            return i;
        }
    }
    return -1;
}

int BillingSystem::findMeter(int id) {
    for (int i = 0; i < meterCount; i++) {
        if (meters[i].getMeterId() == id) {
            return i;
        }
    }
    return -1;
}

int BillingSystem::findReading(int meterId, int month, int year) {
    for (int i = 0; i < readingCount; i++) {
        if (readings[i].getMeterId() == meterId &&
            readings[i].getMonth() == month &&
            readings[i].getYear() == year) {
            return i;
        }
    }
    return -1;
}

int BillingSystem::findBill(int billId) {
    for (int i = 0; i < billCount; i++) {
        if (bills[i].getBillId() == billId) {
            return i;
        }
    }
    return -1;
}

int BillingSystem::findBillOfMeter(int meterId, int month, int year) {
    for (int i = 0; i < billCount; i++) {
        if (bills[i].getMeterId() == meterId &&
            bills[i].getMonth() == month &&
            bills[i].getYear() == year) {
            return i;
        }
    }
    return -1;
}

// The new bill gets the biggest bill number + 1
int BillingSystem::nextBillId() {
    int biggest = 0;
    for (int i = 0; i < billCount; i++) {
        if (bills[i].getBillId() > biggest) {
            biggest = bills[i].getBillId();
        }
    }
    return biggest + 1;
}

// ---------- Make the arrays bigger ----------
// Steps: make a bigger array, copy the old items, delete the old array.

void BillingSystem::growCustomers() {
    int newCapacity = customerCapacity * 2;
    Customer* bigger = new Customer[newCapacity];
    for (int i = 0; i < customerCount; i++) {
        bigger[i] = customers[i];
    }
    delete[] customers;
    customers = bigger;
    customerCapacity = newCapacity;
}

void BillingSystem::growMeters() {
    int newCapacity = meterCapacity * 2;
    Meter* bigger = new Meter[newCapacity];
    for (int i = 0; i < meterCount; i++) {
        bigger[i] = meters[i];
    }
    delete[] meters;
    meters = bigger;
    meterCapacity = newCapacity;
}

void BillingSystem::growReadings() {
    int newCapacity = readingCapacity * 2;
    Reading* bigger = new Reading[newCapacity];
    for (int i = 0; i < readingCount; i++) {
        bigger[i] = readings[i];
    }
    delete[] readings;
    readings = bigger;
    readingCapacity = newCapacity;
}

void BillingSystem::growBills() {
    int newCapacity = billCapacity * 2;
    Bill* bigger = new Bill[newCapacity];
    for (int i = 0; i < billCount; i++) {
        bigger[i] = bills[i];
    }
    delete[] bills;
    bills = bigger;
    billCapacity = newCapacity;
}

// ---------- Main menu ----------

void BillingSystem::showMenu() {
    cout << endl;
    cout << "====== ELECTRICITY BILLING SYSTEM ======" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Display Records" << endl;
    cout << "3. Search Record" << endl;
    cout << "4. Update Record" << endl;
    cout << "5. Delete Record" << endl;
    cout << "6. Main Transaction (Bill)" << endl;
    cout << "7. Report" << endl;
    cout << "8. Save / Load" << endl;
    cout << "9. Exit" << endl;
}

// ---------- 1. Add Record ----------

void BillingSystem::addRecord() {
    cout << endl << "--- Add Record ---" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Meter" << endl;
    cout << "3. Reading" << endl;
    int choice = askNumber("Choose: ");
    if (choice == 1) {
        addCustomer();
    } else if (choice == 2) {
        addMeter();
    } else if (choice == 3) {
        addReading();
    } else {
        cout << "Wrong choice." << endl;
    }
}

void BillingSystem::addCustomer() {
    try {
        int id = askNumber("Customer ID: ");
        if (findCustomer(id) != -1) {
            cout << "This customer ID is already used." << endl;
            return;
        }
        string name = askText("Name: ");
        string address = askText("Address: ");
        string phone = askText("Phone (10 digits): ");
        int type = askNumber("Plan (1 = Home, 2 = Shop): ");

        Customer c(id, name, address, phone, type);   // this checks all values

        if (customerCount == customerCapacity) {
            growCustomers();
        }
        customers[customerCount] = c;
        customerCount++;
        cout << "Customer added." << endl;
    } catch (const char* message) {
        cout << "Error: " << message << endl;
    }
}

void BillingSystem::addMeter() {
    try {
        int meterId = askNumber("Meter ID: ");
        if (findMeter(meterId) != -1) {
            cout << "This meter ID is already used." << endl;
            return;
        }
        int customerId = askNumber("Customer ID who owns this meter: ");
        if (findCustomer(customerId) == -1) {
            cout << "Customer not found. Add the customer first." << endl;
            return;
        }
        string location = askText("Meter location: ");

        Meter m(meterId, customerId, location);

        if (meterCount == meterCapacity) {
            growMeters();
        }
        meters[meterCount] = m;
        meterCount++;
        cout << "Meter added." << endl;
    } catch (const char* message) {
        cout << "Error: " << message << endl;
    }
}

void BillingSystem::addReading() {
    try {
        int meterId = askNumber("Meter ID: ");
        if (findMeter(meterId) == -1) {
            cout << "Meter not found. Add the meter first." << endl;
            return;
        }
        int month = askNumber("Month (1-12): ");
        int year = askNumber("Year (for example 2026): ");
        if (findReading(meterId, month, year) != -1) {
            cout << "A reading for this meter and month already exists." << endl;
            return;
        }
        int previous = askNumber("Previous reading: ");
        int current = askNumber("Current reading: ");

        Reading r(meterId, month, year, previous, current);   // this checks all values

        if (readingCount == readingCapacity) {
            growReadings();
        }
        readings[readingCount] = r;
        readingCount++;
        cout << "Reading added. Units used: " << r.getUnitsUsed() << endl;
    } catch (const char* message) {
        cout << "Error: " << message << endl;
    }
}

// ---------- 2. Display Records ----------

void BillingSystem::displayRecords() {
    cout << endl << "--- Display Records ---" << endl;
    cout << "1. Customers" << endl;
    cout << "2. Meters" << endl;
    cout << "3. Readings" << endl;
    cout << "4. Bills" << endl;
    int choice = askNumber("Choose: ");

    if (choice == 1) {
        if (customerCount == 0) cout << "No customers yet." << endl;
        for (int i = 0; i < customerCount; i++) {
            cout << "-----------------------" << endl;
            customers[i].display();
        }
    } else if (choice == 2) {
        if (meterCount == 0) cout << "No meters yet." << endl;
        for (int i = 0; i < meterCount; i++) {
            cout << "-----------------------" << endl;
            meters[i].display();
        }
    } else if (choice == 3) {
        if (readingCount == 0) cout << "No readings yet." << endl;
        for (int i = 0; i < readingCount; i++) {
            cout << "-----------------------" << endl;
            readings[i].display();
        }
    } else if (choice == 4) {
        if (billCount == 0) cout << "No bills yet." << endl;
        for (int i = 0; i < billCount; i++) {
            cout << "-----------------------" << endl;
            bills[i].display();
        }
    } else {
        cout << "Wrong choice." << endl;
    }
}

// ---------- 3. Search Record ----------

void BillingSystem::searchRecord() {
    searchCustomer();
}

// Find a customer by ID and show the customer, the meters and the bills
void BillingSystem::searchCustomer() {
    int id = askNumber("Customer ID to search: ");
    int position = findCustomer(id);
    if (position == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    cout << endl << "Customer found:" << endl;
    customers[position].display();

    cout << endl << "Meters of this customer:" << endl;
    int found = 0;
    for (int i = 0; i < meterCount; i++) {
        if (meters[i].getCustomerId() == id) {
            cout << "-----------------------" << endl;
            meters[i].display();
            found++;
        }
    }
    if (found == 0) cout << "None." << endl;

    cout << endl << "Bills of this customer:" << endl;
    found = 0;
    for (int i = 0; i < billCount; i++) {
        if (bills[i].getCustomerId() == id) {
            cout << "-----------------------" << endl;
            bills[i].display();
            found++;
        }
    }
    if (found == 0) cout << "None." << endl;
}

// ---------- 4. Update Record ----------

void BillingSystem::updateRecord() {
    updateCustomer();
}

void BillingSystem::updateCustomer() {
    try {
        int id = askNumber("Customer ID to update: ");
        int position = findCustomer(id);
        if (position == -1) {
            cout << "Customer not found." << endl;
            return;
        }
        cout << "Press Enter (or type 0 for the plan) to keep the old value." << endl;

        string name = askText("New name: ");
        if (name != "") {
            customers[position].setName(name);
        }
        string address = askText("New address: ");
        if (address != "") {
            customers[position].setAddress(address);
        }
        string phone = askText("New phone: ");
        if (phone != "") {
            customers[position].setPhone(phone);
        }
        int type = askNumber("New plan (1 = Home, 2 = Shop, 0 = keep): ");
        if (type != 0) {
            customers[position].setPlanType(type);
        }
        cout << "Customer updated." << endl;
    } catch (const char* message) {
        cout << "Error: " << message << endl;
    }
}

// ---------- 5. Delete Record ----------

void BillingSystem::deleteRecord() {
    cout << endl << "--- Delete Record ---" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Meter" << endl;
    cout << "3. Reading" << endl;
    int choice = askNumber("Choose: ");
    if (choice == 1) {
        deleteCustomer();
    } else if (choice == 2) {
        deleteMeter();
    } else if (choice == 3) {
        deleteReading();
    } else {
        cout << "Wrong choice." << endl;
    }
}

// A customer can be deleted only if the customer has no meters
void BillingSystem::deleteCustomer() {
    int id = askNumber("Customer ID to delete: ");
    int position = findCustomer(id);
    if (position == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    for (int i = 0; i < meterCount; i++) {
        if (meters[i].getCustomerId() == id) {
            cout << "This customer still has a meter. Delete the meter first." << endl;
            return;
        }
    }
    // move all later customers one step to the left
    for (int i = position; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1];
    }
    customerCount--;
    cout << "Customer deleted." << endl;
}

// A meter can be deleted only if it has no readings
void BillingSystem::deleteMeter() {
    int id = askNumber("Meter ID to delete: ");
    int position = findMeter(id);
    if (position == -1) {
        cout << "Meter not found." << endl;
        return;
    }
    for (int i = 0; i < readingCount; i++) {
        if (readings[i].getMeterId() == id) {
            cout << "This meter still has readings. Delete the readings first." << endl;
            return;
        }
    }
    for (int i = position; i < meterCount - 1; i++) {
        meters[i] = meters[i + 1];
    }
    meterCount--;
    cout << "Meter deleted." << endl;
}

void BillingSystem::deleteReading() {
    int meterId = askNumber("Meter ID of the reading: ");
    int month = askNumber("Month (1-12): ");
    int year = askNumber("Year: ");
    int position = findReading(meterId, month, year);
    if (position == -1) {
        cout << "Reading not found." << endl;
        return;
    }
    for (int i = position; i < readingCount - 1; i++) {
        readings[i] = readings[i + 1];
    }
    readingCount--;
    cout << "Reading deleted." << endl;
}

// ---------- 6. Main Transaction: make and pay bills ----------

void BillingSystem::mainTransaction() {
    cout << endl << "--- Main Transaction ---" << endl;
    cout << "1. Make a bill from a reading" << endl;
    cout << "2. Pay a bill" << endl;
    int choice = askNumber("Choose: ");
    if (choice == 1) {
        generateBill();
    } else if (choice == 2) {
        payBill();
    } else {
        cout << "Wrong choice." << endl;
    }
}

void BillingSystem::generateBill() {
    try {
        int meterId = askNumber("Meter ID: ");
        int month = askNumber("Month (1-12): ");
        int year = askNumber("Year: ");

        int m = findMeter(meterId);
        if (m == -1) {
            cout << "Meter not found." << endl;
            return;
        }
        int r = findReading(meterId, month, year);
        if (r == -1) {
            cout << "No reading for this month. Add the reading first." << endl;
            return;
        }
        if (findBillOfMeter(meterId, month, year) != -1) {
            cout << "The bill for this month is already made." << endl;
            return;
        }
        int c = findCustomer(meters[m].getCustomerId());
        if (c == -1) {
            cout << "The owner of this meter was not found." << endl;
            return;
        }

        Bill b(nextBillId(), customers[c].getCustomerId(), meterId, month, year, readings[r].getUnitsUsed());

        // Pick the price plan by the customer's plan type.
        // The parent pointer (Tariff*) can hold a Home plan or a Shop plan.
        Tariff* plan;
        if (customers[c].getPlanType() == 1) {
            plan = new HomeTariff();
        } else {
            plan = new ShopTariff();
        }
        b.calculateAmount(plan);     // the right plan works out the amount
        delete plan;                 // free the memory

        if (billCount == billCapacity) {
            growBills();
        }
        bills[billCount] = b;
        billCount++;

        cout << endl << "Bill made:" << endl;
        b.display();
    } catch (const char* message) {
        cout << "Error: " << message << endl;
    }
}

void BillingSystem::payBill() {
    int id = askNumber("Bill ID to pay: ");
    int position = findBill(id);
    if (position == -1) {
        cout << "Bill not found." << endl;
        return;
    }
    if (bills[position].getIsPaid()) {
        cout << "This bill is already paid." << endl;
        return;
    }
    bills[position].markAsPaid();
    cout << "Payment done. Bill " << id << " is now paid." << endl;
}

// ---------- 7. Report ----------

void BillingSystem::showReport() {
    int totalUnits = 0;
    int paidCount = 0;
    int unpaidCount = 0;
    double totalAmount = 0;
    double paidAmount = 0;
    double unpaidAmount = 0;

    for (int i = 0; i < billCount; i++) {
        totalUnits = totalUnits + bills[i].getUnits();
        totalAmount = totalAmount + bills[i].getAmount();
        if (bills[i].getIsPaid()) {
            paidCount++;
            paidAmount = paidAmount + bills[i].getAmount();
        } else {
            unpaidCount++;
            unpaidAmount = unpaidAmount + bills[i].getAmount();
        }
    }

    cout << endl << "========== REPORT ==========" << endl;
    cout << "Total customers: " << customerCount << endl;
    cout << "Total meters: " << meterCount << endl;
    cout << "Total readings: " << readingCount << endl;
    cout << "Total bills: " << billCount << endl;
    cout << "Total units used: " << totalUnits << endl;
    cout << "Total amount billed: " << totalAmount << endl;
    cout << "Paid bills: " << paidCount << " (amount " << paidAmount << ")" << endl;
    cout << "Unpaid bills: " << unpaidCount << " (amount " << unpaidAmount << ")" << endl;
}

// ---------- 8. Save / Load ----------

void BillingSystem::saveLoadMenu() {
    cout << endl << "--- Save / Load ---" << endl;
    cout << "1. Save data to files" << endl;
    cout << "2. Load data from files (this replaces what is on screen now)" << endl;
    int choice = askNumber("Choose: ");
    if (choice == 1) {
        saveData();
    } else if (choice == 2) {
        loadData();
    } else {
        cout << "Wrong choice." << endl;
    }
}

void BillingSystem::saveData() {
    try {
        fileManager.saveCustomers("Data/customers.txt", customers, customerCount);
        fileManager.saveMeters("Data/meters.txt", meters, meterCount);
        fileManager.saveReadings("Data/readings.txt", readings, readingCount);
        fileManager.saveBills("Data/bills.txt", bills, billCount);
        cout << "Data saved." << endl;
    } catch (const char* message) {
        cout << "Error: " << message << endl;
    }
}

void BillingSystem::loadData() {
    // Throw away the old arrays and make new ones that are big enough
    delete[] customers;
    customerCapacity = fileManager.countLines("Data/customers.txt") + 10;
    customers = new Customer[customerCapacity];
    customerCount = fileManager.loadCustomers("Data/customers.txt", customers, customerCapacity);

    delete[] meters;
    meterCapacity = fileManager.countLines("Data/meters.txt") + 10;
    meters = new Meter[meterCapacity];
    meterCount = fileManager.loadMeters("Data/meters.txt", meters, meterCapacity);

    delete[] readings;
    readingCapacity = fileManager.countLines("Data/readings.txt") + 10;
    readings = new Reading[readingCapacity];
    readingCount = fileManager.loadReadings("Data/readings.txt", readings, readingCapacity);

    delete[] bills;
    billCapacity = fileManager.countLines("Data/bills.txt") + 10;
    bills = new Bill[billCapacity];
    billCount = fileManager.loadBills("Data/bills.txt", bills, billCapacity);

    cout << "Data loaded: " << customerCount << " customers, " << meterCount << " meters, "
         << readingCount << " readings, " << billCount << " bills." << endl;
}
