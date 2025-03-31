#ifndef ATM_H
#define ATM_H

#include <string>
#include <vector>
#include <memory>


class Account;

class ATM {
private:
    std::vector<std::shared_ptr<Account>> accounts;
    
    // Pointer to the currently authenticated account.
    Account* currentAccount;
    
    bool isAuthenticated;

public:
    ATM();
    ~ATM();

    void addAccount(const std::shared_ptr<Account>& account);

    bool authenticate(const std::string& accountNumber, const std::string& pin);

    void deposit(double amount);

    bool withdraw(double amount);
};

#endif // ATM_H

