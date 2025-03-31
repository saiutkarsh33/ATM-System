#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <mutex>

class ATM;

class Account {
private:
    std::string accountId;
    std::string pin;
    double money;
    mutable std::mutex mtx; 

public:
    Account(const std::string& accountId, const std::string& pin, double money);

    bool withdraw(double amount, ATM& atm);

    void deposit(double amount, ATM& atm);

    bool authenticate(const std::string& inputPin) const;

    std::string getAccountId() const;
    double getBalance() const;

    // Move semantics for efficient transfers
    Account(Account&& other) noexcept;
    Account& operator=(Account&& other) noexcept;

    Account(const Account&);
    Account& operator=(const Account&);

    // Destructor.
    ~Account();

    // Rule of 5

};

#endif // ACCOUNT_H
