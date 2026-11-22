#include <iostream>
#include <string>
using namespace std;

class Account {
    int accNo;
    string holder, type;
    double balance;
public:
    static int total;
    Account() : accNo(0), balance(0) {}

    Account &enter() {
        cout << "Account number: "; cin >> this->accNo;
        cout << "Holder name: "; cin >> this->holder;
        cout << "Balance: "; cin >> this->balance;
        cout << "Type (Savings/Current): "; cin >> this->type;
        total++;
        return *this;
    }
    void display() const {
        cout << "Acc No: " << accNo << " | Holder: " << holder
             << " | Type: " << type << " | Balance: " << balance << "\n";
    }
    static void showTotal() { cout << "Total accounts: " << total << "\n"; }
    friend void compareBalance(const Account &a, const Account &b);
    inline double updatedBalance(double rate) const { return balance + balance * rate / 100; }
    double getBalance() const { return balance; }
};
int Account::total = 0;

void compareBalance(const Account &a, const Account &b) {
    if (a.balance > b.balance) cout << "Account " << a.accNo << " has the higher balance.\n";
    else if (a.balance < b.balance) cout << "Account " << b.accNo << " has the higher balance.\n";
    else cout << "Both accounts have equal balance.\n";
}

int main() {
    Account accounts[10];
    int n = 0, choice, i, j;
    do {
        cout << "\n1.Enter account 2.Display all 3.Total count 4.Compare two accounts "
             << "5.Updated balance (interest) 0.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            if (n < 10) accounts[n++].enter();
            else cout << "Limit reached.\n";
            break;
        case 2:
            for (i = 0; i < n; i++) accounts[i].display();
            break;
        case 3:
            Account::showTotal();
            break;
        case 4:
            cout << "Enter two account indexes (1-" << n << "): ";
            cin >> i >> j;
            if (i < 1 || j < 1 || i > n || j > n) cout << "Invalid index.\n";
            else compareBalance(accounts[i - 1], accounts[j - 1]);
            break;
        case 5: {
            double rate;
            cout << "Enter index and interest rate %: ";
            cin >> i >> rate;
            if (i < 1 || i > n) cout << "Invalid index.\n";
            else cout << "Updated balance: " << accounts[i - 1].updatedBalance(rate) << "\n";
            break;
        }
        }
    } while (choice != 0);
    return 0;
}
