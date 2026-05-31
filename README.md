# Bank Account Simulator (C++)

A command-line banking system built in C++ demonstrating core OOP principles.

## Features

- Create **Savings** and **Current** accounts
- Deposit, withdraw, and transfer between accounts
- Interest application (Savings accounts — 4% annual)
- Overdraft protection (Current accounts — Rs.5000 limit)
- Withdrawal limit enforcement (Savings — 3 free, Rs.25 fee after)
- **File persistence** — accounts save to `data.txt` and reload on next run

## Concepts Demonstrated

| Concept | Where Used |
|---|---|
| Abstract base class | `Account` with pure virtual methods |
| Inheritance | `SavingsAccount`, `CurrentAccount` extend `Account` |
| Polymorphism | Vector of `Account*` holds both types |
| Smart pointers | `std::unique_ptr<Account>` — no manual delete |
| Dynamic cast | `applyInterest()` — safely checks runtime type |
| File I/O | `saveAccounts()` / `loadAccounts()` with CSV format |
| State machine | `MAIN_MENU → ACCOUNT_SELECTED → EXIT_APP` |

## Build & Run

```bash
g++ -std=c++14 Account.cpp SavingsAccount.cpp CurrentAccount.cpp main.cpp -o bank
.\bank.exe
```