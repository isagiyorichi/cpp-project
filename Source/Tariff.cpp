#include "Tariff.h"

Tariff::Tariff() {
    planName = "Default";
    fixedFee = 0;
}

Tariff::Tariff(string name, double fee) {
    planName = name;
    fixedFee = fee;
}

Tariff::~Tariff() {
}

string Tariff::getPlanName() {
    return planName;
}

double Tariff::getFixedFee() {
    return fixedFee;
}

// The parent version is only a backup. Children replace it.
double Tariff::calculateAmount(int units) {
    return fixedFee;
}

// Home plan: fixed fee is 50
HomeTariff::HomeTariff() : Tariff("Home", 50) {
}

// Home price: first 100 units cost Rs 4 each,
// units after 100 cost Rs 6 each
double HomeTariff::calculateAmount(int units) {
    if (units < 0) {
        throw "Units cannot be negative";   // this is exception handling
    }
    double amount;
    if (units <= 100) {
        amount = units * 4;
    } else {
        amount = 100 * 4 + (units - 100) * 6;
    }
    return amount + fixedFee;
}

// Shop plan: fixed fee is 150
ShopTariff::ShopTariff() : Tariff("Shop", 150) {
}

// Shop price: every unit costs Rs 8
double ShopTariff::calculateAmount(int units) {
    if (units < 0) {
        throw "Units cannot be negative";
    }
    return units * 8 + fixedFee;
}
