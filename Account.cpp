#include "Account.hpp"
#include <utility>
#include <mutex>        
#include <iostream>

Account::Account(const std::string& accountId, const std::string& pin, double money)
    : accountId(accountId), pin(pin), money(money) {}


bool Account::withdraw(double amount, ATM& atm) {
    std::lock_guard<std::mutex> lock(mtx);
    if (money >= amount) {
        money -= amount;
        return true;
    }
    return false;
}

void Account::deposit(double amount, ATM& atm) {
    std::lock_guard<std::mutex> lock(mtx);
    money += amount;
}

bool Account::authenticate(const std::string& inputPin) const {
    return (inputPin == pin);
}

std::string Account::getAccountId() const {
    return accountId;
}

double Account::getBalance() const {
    std::lock_guard<std::mutex> lock(mtx);
    return money;
}

// Copy constructor: Copies the account's data in a thread-safe manner.
Account::Account(const Account& other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    accountId = other.accountId;
    pin = other.pin;
    money = other.money;
}

// Copy assignment operator: Copies data from 'other' into this account.
Account& Account::operator=(const Account& other) {
    if (this != &other) {
        std::scoped_lock lock(mtx, other.mtx);
        accountId = other.accountId;
        pin = other.pin;
        money = other.money;
    }
    return *this;
}

// Move Constructor, creating "this" from scratch using move semantics
Account::Account(Account&& other) noexcept {
    std::lock_guard<std::mutex> lock(other.mtx);
    accountId = std::move(other.accountId);
    pin = std::move(other.pin);
    money = other.money;
}

// Move Assignment Operator: Both destination and source object has already been constructed
// and might be accessed concurrently by other threads
Account& Account::operator=(Account&& other) noexcept {
    if (this != &other) {
        // Locks both mutexes in a deadlock free manner
        std::scoped_lock lock(mtx, other.mtx);
        accountId = std::move(other.accountId);
        pin = std::move(other.pin);
        money = other.money;
    }
    // returns a reference to the current object, mostly for chaining
    return *this;
}

Account::~Account() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Destroying Account: " << accountId << std::endl;
}

