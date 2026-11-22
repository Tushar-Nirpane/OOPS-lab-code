#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accNo;
    string name;
    float balance;
    string accType;

    static int count;

public:
    BankAccount() {
        accNo = 0;
        name = "";
        balance = 0.0;
        accType = "";
        count++;
    }

    void input(int accNo, string name, float balance, string accType) {
        this->accNo = accNo;
        this->name = name;
        this->balance = balance;
        this->accType = accType;
    }

    void display() {
        cout << "\nAccount Number : " << accNo << endl;
        cout << "\nHolder Name : " << name << endl;
        cout << "\nAccount Type : " << accType << endl;
        cout << "\nBalance : " << balance << endl;
    }

    static void showTotal() {
        cout << "\nTotal Accounts Created: " << count << endl;
    }

    inline void addInterest(float rate) {
        balance += (balance * rate) / 100;
        cout << "\nUpdated Balance for " << name << " after interest: "
             << balance << endl;
    }

    friend void compareBalance(BankAccount b1, BankAccount b2);
};

int BankAccount::count = 0;

void compareBalance(BankAccount b1, BankAccount b2) {
    cout << "\n--- Balance Comparison ---" << endl;
    if (b1.balance > b2.balance) {
        cout << b1.name << " has a higher balance than " << b2.name << endl;
    } else if (b2.balance > b1.balance) {
        cout << b2.name << " has a higher balance than " << b1.name << endl;
    } else {
        cout << "Both have the same balance." << endl;
    }
}

int main() {
    BankAccount a1, a2;

    int num;
    string n, type;
    float bal;

    cout << "Enter Account 1 Details:" << endl;
    cout << "Account Number: ";
    cin >> num;
    cout << "Holder Name: ";
    cin >> n;
    cout << "Balance: ";
    cin >> bal;
    cout << "Account Type (Savings/Current): ";
    cin >> type;
    a1.input(num, n, bal, type);

    cout << "\nEnter Account 2 Details:" << endl;
    cout << "Account Number: ";
    cin >> num;
    cout << "\nHolder Name: ";
    cin >> n;
    cout << "\nBalance: ";
    cin >> bal;
    cout << "\nAccount Type (Savings/Current): ";
    cin >> type;
    a2.input(num, n, bal, type);

    cout << "\n--- Account 1 ---";
    a1.display();
    cout << "\n--- Account 2 ---";
    a2.display();

    BankAccount::showTotal();

    compareBalance(a1, a2);

    a1.addInterest(5.0);

    return 0;
}
