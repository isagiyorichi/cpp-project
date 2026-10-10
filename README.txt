ELECTRICITY BILLING SYSTEM
Enrollment Number: IU2541230461
Project Code: CPP29
Subject: Object Oriented Programming with UML (CE0316)
GitHub: https://github.com/isagiyorichi/cpp-project

ABOUT
This program makes electricity bills. It stores customers, meters and
meter readings. It works out the bill amount from the units used and
the customer's price plan (Home or Shop). All data is saved in files.

FOLDERS
Source/       - all .h and .cpp files
Data/         - saved data files (customers, meters, readings, bills)
Diagrams/     - UML diagrams
Executable/   - the compiled program
Screenshots/  - program screenshots

CLASSES
Customer, Meter, Reading, Bill, Tariff (with HomeTariff and ShopTariff),
FileManager, BillingSystem

HOW TO COMPILE
g++ Source/*.cpp -o Executable/Project

HOW TO RUN
Run it from the main project folder (the folder that has Data and Source):
./Executable/Project

MENU
1. Add Record        (customer, meter or reading)
2. Display Records
3. Search Record     (by customer ID)
4. Update Record     (customer)
5. Delete Record     (customer, meter or reading)
6. Main Transaction  (make a bill, pay a bill)
7. Report
8. Save / Load
9. Exit              (saves automatically)

PRICE PLANS
Home plan: fixed fee Rs 50. First 100 units Rs 4 each, then Rs 6 each.
Shop plan: fixed fee Rs 150. Every unit Rs 8.

SAVING
The program loads the old data when it starts and saves when you
choose Exit. The files are in the Data folder.
