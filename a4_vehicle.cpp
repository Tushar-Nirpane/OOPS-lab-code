#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string number;
public:
    Vehicle(const string &n) : number(n) {}
    virtual double rent(int days) const = 0;
    virtual string type() const = 0;
    virtual ~Vehicle() { cout << "Vehicle " << number << " removed from fleet.\n"; }
};

class Car : public Vehicle {
public:
    Car(const string &n) : Vehicle(n) {}
    double rent(int days) const override { return 1500.0 * days; }
    string type() const override { return "Car"; }
};

class Bike : public Vehicle {
public:
    Bike(const string &n) : Vehicle(n) {}
    double rent(int days) const override { return 500.0 * days; }
    string type() const override { return "Bike"; }
};

class Truck : public Vehicle {
public:
    Truck(const string &n) : Vehicle(n) {}
    double rent(int days) const override { return 3000.0 * days; }
    string type() const override { return "Truck"; }
};

int main() {
    Vehicle *fleet[20];
    int count = 0, choice, days, i;
    string num;
    do {
        cout << "\n1.Add Car 2.Add Bike 3.Add Truck 4.Rent vehicle 5.Remove vehicle 0.Exit\nChoice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 3) {
            if (count == 20) { cout << "Fleet full.\n"; continue; }
            cout << "Vehicle number: "; cin >> num;
            if (choice == 1) fleet[count] = new Car(num);
            else if (choice == 2) fleet[count] = new Bike(num);
            else fleet[count] = new Truck(num);
            count++;
            cout << "Added.\n";
        } else if (choice == 4) {
            cout << "Enter index (0-" << count - 1 << ") and days: ";
            cin >> i >> days;
            if (i < 0 || i >= count) { cout << "Invalid index.\n"; continue; }
            cout << fleet[i]->type() << " rent for " << days << " days: Rs. "
                 << fleet[i]->rent(days) << "\n";
        } else if (choice == 5) {
            cout << "Enter index to remove: "; cin >> i;
            if (i < 0 || i >= count) { cout << "Invalid index.\n"; continue; }
            delete fleet[i];
            fleet[i] = fleet[count - 1];
            count--;
            cout << "Removed.\n";
        }
    } while (choice != 0);
    for (i = 0; i < count; i++) delete fleet[i];
    return 0;
}
