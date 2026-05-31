#include "CurrentAccount.h"
#include <iostream>

CurrentAccount::CurrentAccount(std::string accNum, std::string name,
                                double initialBalance, double overdraft)
    : Account(accNum, name, initialBalance), overdraftLimit(overdraft) {}

void CurrentAccount::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid deposit amount.\n";
        return;
    }
    balance += amount;
    std::cout << "Deposited Rs." << amount << ". New balance: Rs." << balance << "\n";
}

void CurrentAccount::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }
    if (amount > balance + overdraftLimit) {
        std::cout << "Exceeds overdraft limit of Rs." << overdraftLimit << ".\n";
        return;
    }
    balance -= amount;
    if (balance < 0)
        std::cout << "Warning: Account in overdraft. Balance: Rs." << balance << "\n";
    else
        std::cout << "Withdrew Rs." << amount << ". New balance: Rs." << balance << "\n";
}

void CurrentAccount::displayInfo() const {
    std::cout << "\n[Current Account]\n"
              << "Account No    : " << accountNumber << "\n"
              << "Owner         : " << ownerName << "\n"
              << "Balance       : Rs." << balance << "\n"
              << "Overdraft Lmt : Rs." << overdraftLimit << "\n";
}

std::string CurrentAccount::getType() const { return "CURRENT"; }