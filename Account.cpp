#include "Account.h"
#include <iostream>

Account::Account(std::string accNum, std::string name, double initialBalance)
    : accountNumber(accNum), ownerName(name), balance(initialBalance) {}

double Account::getBalance() const { return balance; }
std::string Account::getAccountNumber() const { return accountNumber; }
std::string Account::getOwnerName() const { return ownerName; }