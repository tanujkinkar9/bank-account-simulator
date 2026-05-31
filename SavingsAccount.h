#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;      // e.g. 0.04 = 4% annual
    int withdrawalCount;      // Savings accounts limit free withdrawals
    static const int MAX_FREE_WITHDRAWALS = 3;

public:
    SavingsAccount(std::string accNum, std::string name,
                   double initialBalance, double rate);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void displayInfo() const override;
    std::string getType() const override;

    void applyInterest();     // Savings-specific feature
};

#endif