#include "ATM.hpp"
#include "Account.hpp" 
#include <iostream>

ATM::ATM() : currentAccount(nullptr), isAuthenticated(false) {}

ATM::~ATM() {
    // Clear vector if needed (shared_ptr will automatically release resources).
    accounts.clear();
}

void ATM::addAccount(const std::shared_ptr<Account>& account) {
    accounts.push_back(account);
}

bool ATM::authenticate(const std::string& accountNumber, const std::string& pin) {
    for (const auto& acc : accounts) {
        if (acc->getAccountId() == accountNumber) {
            if (acc->authenticate(pin)) {
                currentAccount = acc.get();
                isAuthenticated = true;
                std::cout << "Authentication successful for account: " << accountNumber << std::endl;
                return true;
            } else {
                std::cout << "Incorrect PIN for account: " << accountNumber << std::endl;
                isAuthenticated = false;
                currentAccount = nullptr;
                return false;
            }
        }
    }
    std::cout << "Account not found: " << accountNumber << std::endl;
    isAuthenticated = false;
    currentAccount = nullptr;
    return false;
}

void ATM::deposit(double amount) {
    if (currentAccount && isAuthenticated) {
        currentAccount->deposit(amount, *this);
    } else {
        std::cout << "Deposit failed: No authenticated account." << std::endl;
    }
}

bool ATM::withdraw(double amount) {
    if (currentAccount && isAuthenticated) {
        return currentAccount->withdraw(amount, *this);
    } else {
        std::cout << "Withdrawal failed: No authenticated account." << std::endl;
        return false;
    }
}
