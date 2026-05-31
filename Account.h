#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;

public:
    Account(std::string accNum, std::string name, double initialBalance);

    // Pure virtual — every derived class MUST implement these
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void displayInfo() const = 0;
    virtual std::string getType() const = 0;

    // Concrete methods shared by all accounts
    double getBalance() const;
    std::string getAccountNumber() const;
    std::string getOwnerName() const;

    virtual ~Account() {}  // Virtual destructor — important with inheritance
};

#endif