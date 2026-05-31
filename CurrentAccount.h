#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
private:
    double overdraftLimit;    // How much they can go below zero

public:
    CurrentAccount(std::string accNum, std::string name,
                   double initialBalance, double overdraft);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void displayInfo() const override;
    std::string getType() const override;
};

#endif