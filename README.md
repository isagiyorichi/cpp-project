# Electricity Billing System

**Enrollment Number:** IU2541230461
**Project Code:** CPP29
**Subject:** Object Oriented Programming with UML (CE0316)

## About the Project
This is a C++ program that makes electricity bills. It keeps the records of customers, meters and meter readings. It works out the bill amount from the units used and the customer's price plan (Home or Shop). All records are saved in files, so they are still there when the program is opened again.

## Features
- Add, display, search, update and delete records
- Make a bill from a meter reading
- Pay a bill
- Report of total units, total amount, paid and unpaid bills
- Save and load data from files
- Checks on the input, with error messages for wrong values

## Classes
| Class | Job |
|---|---|
| Customer | Keeps the details of a customer |
| Meter | Keeps the details of a meter |
| Reading | Keeps the previous and current meter numbers for a month |
| Bill | Keeps the units used, the amount and the paid status |
| Tariff | Parent class for price plans |
| HomeTariff, ShopTariff | Child classes of Tariff. Each works out the amount in its own way |
| FileManager | Saves and loads the records |
| BillingSystem | Keeps all the records and does the work for the menu |

## OOP Concepts Used
- Classes and objects
- Encapsulation (private data with get and set functions)
- Default and parameterized constructors, and destructors
- Inheritance (HomeTariff and ShopTariff come from Tariff)
- Runtime polymorphism (virtual function `calculateAmount`)
- Dynamic memory (`new` and `delete[]`)
- File handling
- Validation and exception handling

## Price Plans
| Plan | Fixed fee | Price per unit |
|---|---|---|
| Home | Rs 50 | First 100 units Rs 4 each, then Rs 6 each |
| Shop | Rs 150 | Rs 8 for every unit |

## Folders
- `Source/` : all .h and .cpp files
- `Data/` : saved data files
- `Diagrams/` : UML diagrams
- `Executable/` : the compiled program
- `Screenshots/` : program screenshots

## How to Compile and Run
Compile:

    g++ Source/*.cpp -o Executable/Project

Run it from the main project folder (the folder that has `Data` and `Source`):

    ./Executable/Project

## Menu
1. Add Record
2. Display Records
3. Search Record
4. Update Record
5. Delete Record
6. Main Transaction (make a bill, pay a bill)
7. Report
8. Save / Load
9. Exit (saves automatically)
