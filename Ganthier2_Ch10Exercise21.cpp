#include <iostream>
#include <iomanip>

using namespace std;

// ========================================================================
// Base Class: bankAccount
// ========================================================================
class bankAccount {
protected:
    int accountNumber;
    double balance;

public:
    // Constructors
    bankAccount(int acctNo = 0, double bal = 0.0) : accountNumber(acctNo), balance(bal) {}

    // Setters and Getters
    void setAccountNumber(int acctNo) {
        accountNumber = acctNo;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    // Account Operations
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " into account #" << accountNumber << ".\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Withdrew $" << amount << " from account #" << accountNumber << ".\n";
        } else {
            cout << "Transaction Failed: Insufficient funds or invalid amount.\n";
        }
    }

    virtual void printAccountInfo() const {
        cout << "Account Number: " << accountNumber << "\n"
             << "Balance: $" << fixed << setprecision(2) << balance << "\n";
    }
};

// ========================================================================
// Derived Class: checkingAccount
// ========================================================================
class checkingAccount : public bankAccount {
private:
    double interestRate;
    double minBalance;
    double serviceCharge;

public:
    // Constructors
    checkingAccount(int acctNo = 0, double bal = 0.0, double intRate = 0.0, double minBal = 0.0, double servChg = 0.0)
        : bankAccount(acctNo, bal), interestRate(intRate), minBalance(minBal), serviceCharge(servChg) {}

    // Setters and Getters
    void setInterestRate(double intRate) {
        interestRate = intRate;
    }

    double getInterestRate() const {
        return interestRate;
    }

    void setMinBalance(double minBal) {
        minBalance = minBal;
    }

    double getMinBalance() const {
        return minBalance;
    }

    void setServiceCharges(double servChg) {
        serviceCharge = servChg;
    }

    double getServiceCharges() const {
        return serviceCharge;
    }

    // Account Operations
    void postInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Interest of $" << interest << " posted to Checking Account #" << accountNumber << ".\n";
    }

    bool verifyMinimumBalance() {
        if (balance < minBalance) {
            balance -= serviceCharge;
            cout << "*** Balance fell below minimum of $" << minBalance 
                 << ". Service charge of $" << serviceCharge << " applied. ***\n";
            return true; // True indicates the charge was applied
        }
        return false;
    }

    void writeCheck(double amount) {
        cout << "Writing check for $" << amount << "...\n";
        withdraw(amount); // Uses overridden withdraw
    }

    void withdraw(double amount) override {
        bankAccount::withdraw(amount);
        verifyMinimumBalance();
    }

    void printAccountInfo() const override {
        cout << "--- Checking Account Info ---\n";
        bankAccount::printAccountInfo();
        cout << "Interest Rate: " << (interestRate * 100) << "%\n"
             << "Minimum Balance Requirement: $" << minBalance << "\n"
             << "Service Charge Penalty: $" << serviceCharge << "\n"
             << "-----------------------------\n";
    }
};

// ========================================================================
// Derived Class: savingsAccount
// ========================================================================
class savingsAccount : public bankAccount {
private:
    double interestRate;

public:
    // Constructors
    savingsAccount(int acctNo = 0, double bal = 0.0, double intRate = 0.0)
        : bankAccount(acctNo, bal), interestRate(intRate) {}

    // Setters and Getters
    void setInterestRate(double intRate) {
        interestRate = intRate;
    }

    double getInterestRate() const {
        return interestRate;
    }

    // Account Operations
    void postInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Interest of $" << interest << " posted to Savings Account #" << accountNumber << ".\n";
    }

    void withdraw(double amount) override {
        cout << "Attempting withdrawal from savings...\n";
        bankAccount::withdraw(amount);
    }

    void printAccountInfo() const override {
        cout << "--- Savings Account Info ---\n";
        bankAccount::printAccountInfo();
        cout << "Interest Rate: " << (interestRate * 100) << "%\n"
             << "----------------------------\n";
    }
};

// ========================================================================
// Main Execution / Test Program
// ========================================================================
int main() {
    // Format console output for currency
    cout << fixed << setprecision(2);

    cout << "\n=== Testing Checking Account ===\n";
    // Initialize: AccNo=1001, Balance=500.00, Interest=2%, MinBal=250.00, Penalty=25.00
    checkingAccount myChecking(1001, 500.00, 0.02, 250.00, 25.00);
    myChecking.printAccountInfo();
    
    myChecking.deposit(150.00);
    myChecking.postInterest();
    
    // Writing a check that brings the balance below the $250.00 minimum
    myChecking.writeCheck(450.00); 
    
    myChecking.printAccountInfo();

    cout << "\n=== Testing Savings Account ===\n";
    // Initialize: AccNo=2001, Balance=1200.00, Interest=4.5%
    savingsAccount mySavings(2001, 1200.00, 0.045);
    mySavings.printAccountInfo();

    mySavings.deposit(300.00);
    mySavings.withdraw(100.00);
    mySavings.postInterest();
    
    // Attempt an overdraw
    mySavings.withdraw(2000.00); 

    mySavings.printAccountInfo();

    return 0;
}

