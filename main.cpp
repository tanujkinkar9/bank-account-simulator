#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "SavingsAccount.h"
#include "CurrentAccount.h"

// ── File I/O ────────────────────────────────────────────────

void saveAccounts(const std::vector<std::unique_ptr<Account>>& accounts) {
    std::ofstream file("data.txt");
    for (const auto& acc : accounts) {
        file << acc->getType() << ","
             << acc->getAccountNumber() << ","
             << acc->getOwnerName() << ","
             << acc->getBalance() << "\n";
    }
    std::cout << "Accounts saved.\n";
}

void loadAccounts(std::vector<std::unique_ptr<Account>>& accounts) {
    std::ifstream file("data.txt");
    if (!file.is_open()) return;   // First run — no file yet, that's fine

    std::string line;
    while (std::getline(file, line)) {
        std::string type, accNum, name, balStr;
        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        type   = line.substr(0, p1);
        accNum = line.substr(p1 + 1, p2 - p1 - 1);
        name   = line.substr(p2 + 1, p3 - p2 - 1);
        balStr = line.substr(p3 + 1);
        double bal = std::stod(balStr);

        if (type == "SAVINGS")
            accounts.push_back(std::make_unique<SavingsAccount>(accNum, name, bal, 0.04));
        else if (type == "CURRENT")
            accounts.push_back(std::make_unique<CurrentAccount>(accNum, name, bal, 5000.0));
    }
    std::cout << "Loaded " << accounts.size() << " account(s).\n";
}

// ── Helpers ──────────────────────────────────────────────────

Account* findAccount(std::vector<std::unique_ptr<Account>>& accounts,
                     const std::string& accNum) {
    for (auto& acc : accounts)
        if (acc->getAccountNumber() == accNum) return acc.get();
    return nullptr;
}

std::string generateAccNum(const std::vector<std::unique_ptr<Account>>& accounts) {
    return "ACC" + std::to_string(1000 + (int)accounts.size() + 1);
}

// ── State Machine ─────────────────────────────────────────────

enum State { MAIN_MENU, ACCOUNT_SELECTED, EXIT_APP };

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    loadAccounts(accounts);

    State state = MAIN_MENU;
    Account* current = nullptr;   // Points to selected account
    int choice;

    std::cout << "\n=== Bank Account Simulator ===\n";

    while (state != EXIT_APP) {

        // ── MAIN MENU state ──
        if (state == MAIN_MENU) {
            std::cout << "\n[Main Menu]\n"
                      << "1. Create Savings Account\n"
                      << "2. Create Current Account\n"
                      << "3. Select Account\n"
                      << "4. List All Accounts\n"
                      << "5. Save & Exit\n"
                      << "Choice: ";
            std::cin >> choice;

            if (choice == 1 || choice == 2) {
                std::string name;
                double initial;
                std::cout << "Owner name: "; std::cin >> name;
                std::cout << "Initial deposit: Rs."; std::cin >> initial;
                std::string accNum = generateAccNum(accounts);

                if (choice == 1)
                    accounts.push_back(
                        std::make_unique<SavingsAccount>(accNum, name, initial, 0.04));
                else
                    accounts.push_back(
                        std::make_unique<CurrentAccount>(accNum, name, initial, 5000.0));

                std::cout << "Account created. Number: " << accNum << "\n";

            } else if (choice == 3) {
                std::string accNum;
                std::cout << "Enter account number: "; std::cin >> accNum;
                current = findAccount(accounts, accNum);
                if (current) {
                    state = ACCOUNT_SELECTED;
                } else {
                    std::cout << "Account not found.\n";
                }

            } else if (choice == 4) {
                if (accounts.empty()) {
                    std::cout << "No accounts yet.\n";
                } else {
                    for (const auto& acc : accounts) acc->displayInfo();
                }

            } else if (choice == 5) {
                saveAccounts(accounts);
                state = EXIT_APP;
            }
        }

        // ── ACCOUNT SELECTED state ──
        else if (state == ACCOUNT_SELECTED) {
            current->displayInfo();
            std::cout << "\n[Account Menu]\n"
                      << "1. Deposit\n"
                      << "2. Withdraw\n"
                      << "3. Transfer\n"
                      << "4. Apply Interest (Savings only)\n"
                      << "5. Back to Main Menu\n"
                      << "Choice: ";
            std::cin >> choice;

            if (choice == 1) {
                double amt;
                std::cout << "Amount: Rs."; std::cin >> amt;
                current->deposit(amt);

            } else if (choice == 2) {
                double amt;
                std::cout << "Amount: Rs."; std::cin >> amt;
                current->withdraw(amt);

            } else if (choice == 3) {
                std::string targetNum;
                double amt;
                std::cout << "Target account number: "; std::cin >> targetNum;
                std::cout << "Amount: Rs."; std::cin >> amt;

                Account* target = findAccount(accounts, targetNum);
                if (!target) {
                    std::cout << "Target account not found.\n";
                } else if (target == current) {
                    std::cout << "Cannot transfer to same account.\n";
                } else {
                    current->withdraw(amt);   // Will check funds/overdraft
                    target->deposit(amt);
                    std::cout << "Transfer complete.\n";
                }

            } else if (choice == 4) {
                // Dynamic cast — only works if it IS a SavingsAccount
                SavingsAccount* sa = dynamic_cast<SavingsAccount*>(current);
                if (sa) sa->applyInterest();
                else std::cout << "Interest only applies to Savings accounts.\n";

            } else if (choice == 5) {
                current = nullptr;
                state = MAIN_MENU;
            }
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}