#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount(std::string accNum, std::string name,
                                double initialBalance, double rate)
    : Account(accNum, name, initialBalance),
      interestRate(rate), withdrawalCount(0) {}

void SavingsAccount::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid deposit amount.\n";
        return;
    }
    balance += amount;
    std::cout << "Deposited Rs." << amount << ". New balance: Rs." << balance << "\n";
}

void SavingsAccount::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds. Savings account cannot overdraft.\n";
        return;
    }

    withdrawalCount++;
    if (withdrawalCount > MAX_FREE_WITHDRAWALS) {
        double fee = 25.0;
        std::cout << "Exceeded free withdrawals. Rs.25 fee applied.\n";
        balance -= fee;
    }

    balance -= amount;
    std::cout << "Withdrew Rs." << amount << ". New balance: Rs." << balance << "\n";
}

void SavingsAccount::applyInterest() {
    double interest = balance * interestRate;
    balance += interest;
    std::cout << "Interest applied: Rs." << interest
              << ". New balance: Rs." << balance << "\n";
}

void SavingsAccount::displayInfo() const {
    std::cout << "\n[Savings Account]\n"
              << "Account No : " << accountNumber << "\n"
              << "Owner      : " << ownerName << "\n"
              << "Balance    : Rs." << balance << "\n"
              << "Interest   : " << interestRate * 100 << "%\n"
              << "Withdrawals: " << withdrawalCount << "/" 
              << MAX_FREE_WITHDRAWALS << " free\n";
}

std::string SavingsAccount::getType() const { return "SAVINGS"; }