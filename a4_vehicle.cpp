#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string model;
    float rate;

public:
    Vehicle(string m, float r) {
        model = m;
        rate = r;
    }

    virtual float getRent(int days) = 0;

    virtual void show() {
        cout << "Model: " << model << " | Daily Rate: $" << rate;
    }

    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    Car(string m, float r) : Vehicle(m, r) {}

    float getRent(int days) {
        return rate * days;
    }

    void show() {
        Vehicle::show();
        cout << " [Car]" << endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(string m, float r) : Vehicle(m, r) {}

    float getRent(int days) {
        return rate * days;
    }

    void show() {
        Vehicle::show();
        cout << " [Bike]" << endl;
    }
};

class Truck : public Vehicle {
public:
    Truck(string m, float r) : Vehicle(m, r) {}

    float getRent(int days) {
        return (rate * days) + 50.0f;
    }

    void show() {
        Vehicle::show();
        cout << " [Truck]" << endl;
    }
};

int main() {
    Vehicle* list[20];
    int count = 0;
    int choice = 0;

    while (choice != 5) {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Add Car" << endl;
        cout << "2. Add Bike" << endl;
        cout << "3. Add Truck" << endl;
        cout << "4. Show All & Calculate Rent" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            string junk;
            cin >> junk;
            cout << "Invalid input! Try again." << endl;
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            if (count >= 20) {
                cout << "Fleet is full (20 vehicles)." << endl;
                continue;
            }
            string m;
            float r;
            cout << "Enter model name: ";
            cin >> m;
            cout << "Enter daily rate: ";
            cin >> r;

            if (choice == 1) list[count++] = new Car(m, r);
            if (choice == 2) list[count++] = new Bike(m, r);
            if (choice == 3) list[count++] = new Truck(m, r);

            cout << "Vehicle added successfully!" << endl;
        }
        else if (choice == 4) {
            if (count == 0) {
                cout << "No vehicles in list!" << endl;
            } else {
                int days;
                cout << "Enter number of rental days: ";
                cin >> days;
                cout << "\n--- Rental Summary ---" << endl;
                for (int i = 0; i < count; i++) {
                    cout << (i + 1) << ". ";
                    list[i]->show();
                    cout << "   Total Rent: $" << list[i]->getRent(days) << endl;
                }
            }
        }
        else if (choice == 5) {
            cout << "Freeing memory and exiting..." << endl;
            for (int i = 0; i < count; i++) {
                delete list[i];
            }
        }
        else {
            cout << "Invalid choice! Enter 1 to 5." << endl;
        }
    }

    return 0;
}
