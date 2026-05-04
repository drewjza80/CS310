#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ========================================================================
// Class Definition
// ========================================================================
class bankAccount {
private:
    string name;
    int accountNumber;
    string type; // "checking" or "saving"
    double balance;
    double interestRate; // Stored as a decimal (e.g., 0.02 for 2%)

    // Static member to auto-assign unique account numbers
    static int nextAccountNumber;

public:
    // Default Constructor
    bankAccount() {
        name = "Unassigned";
        type = "checking";
        balance = 0.0;
        interestRate = 0.0;
        accountNumber = nextAccountNumber++; 
    }

    // Initialization Function
    void initialize(string newName, string accType, double initialBalance, double intRate) {
        name = newName;
        type = accType;
        balance = initialBalance;
        interestRate = intRate;
    }

    // ====================================================================
    // Member Functions (Manipulators)
    // ====================================================================
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " into account #" << accountNumber << ".\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Withdrew $" << amount << " from account #" << accountNumber << ".\n";
        } else if (amount > balance) {
            cout << "Transaction Failed: Insufficient funds in account #" << accountNumber << ".\n";
        } else {
            cout << "Invalid withdrawal amount.\n";
        }
    }

    void applyInterest() {
        double interestEarned = balance * interestRate;
        balance += interestEarned;
        cout << "Interest of $" << interestEarned << " applied to account #" << accountNumber << ".\n";
    }

    void displayAccountInfo() const {
        cout << left << setw(15) << name 
             << setw(10) << accountNumber 
             << setw(12) << type 
             << "$" << setw(10) << balance 
             << (interestRate * 100) << "%\n";
    }
    
    string getName() const {
        return name;
    }
};

// ========================================================================
// Static Member Initialization
// ========================================================================
int bankAccount::nextAccountNumber = 1001; 

// ========================================================================
// Main Execution
// ========================================================================
int main() {
    cout << fixed << setprecision(2);

    // Array of 10 bankAccount objects
    bankAccount customers[10];

    // 1. Populate a few of the customers
    customers[0].initialize("Alice Smith", "checking", 1500.50, 0.01);
    customers[1].initialize("Bob Jones", "saving", 5400.00, 0.045);
    customers[2].initialize("Charlie Day", "saving", 250.00, 0.03);

    // 2. Display the initial state
    cout << "--- Initial Account States ---\n";
    cout << left << setw(15) << "Name" << setw(10) << "Acc Num" << setw(12) << "Type" << setw(11) << "Balance" << "Interest\n";
    cout << "----------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        if (customers[i].getName() != "Unassigned") {
            customers[i].displayAccountInfo();
        }
    }
    cout << "\n";

    // 3. Illustrate Object Manipulation
    cout << "--- Processing Transactions ---\n";
    customers[0].deposit(1200.00);
    customers[1].withdraw(1400.00);
    customers[2].withdraw(500.00); 
    customers[1].applyInterest();
    customers[2].applyInterest();
    
    // 4. Display Final Output
    cout << "\n--- Updated Account States ---\n";
    cout << left << setw(15) << "Name" << setw(10) << "Acc Num" << setw(12) << "Type" << setw(11) << "Balance" << "Interest\n";
    cout << "----------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        if (customers[i].getName() != "Unassigned") {
            customers[i].displayAccountInfo();
        }
    }

    return 0;
}
