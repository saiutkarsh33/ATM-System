#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include "ATM.hpp"
#include "Account.hpp"


int main() {

    auto account = std::make_shared<Account>("ACC001", "1234", 1000.0);

    ATM atm;
    
    atm.addAccount(account);

    if (!atm.authenticate("ACC001", "1234")) {
        std::cout << "Authentication failed. Exiting." << std::endl;
        return 1;
    }
    
    std::vector<std::thread> threads;
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([&atm, i]() {
            std::cout << "Thread " << i << " starting deposit of 100.0" << std::endl;
            atm.deposit(100.0);
            std::cout << "Thread " << i << " finished deposit" << std::endl;
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Final balance: " << account->getBalance() << std::endl;
    return 0;
}
