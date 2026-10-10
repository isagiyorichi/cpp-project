#include <iostream>
#include "BillingSystem.h"
using namespace std;

// main only makes the system, shows the menu and calls the system functions.
int main() {
    BillingSystem app;
    app.loadData();          // start: load the old records

    int choice = 0;
    while (choice != 9) {
        app.showMenu();
        choice = app.askNumber("Enter your choice: ");

        switch (choice) {
            case 1: app.addRecord(); break;
            case 2: app.displayRecords(); break;
            case 3: app.searchRecord(); break;
            case 4: app.updateRecord(); break;
            case 5: app.deleteRecord(); break;
            case 6: app.mainTransaction(); break;
            case 7: app.showReport(); break;
            case 8: app.saveLoadMenu(); break;
            case 9:
                app.saveData();      // exit: save the records first
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Wrong choice. Please type a number from 1 to 9." << endl;
        }
    }
    return 0;
}
