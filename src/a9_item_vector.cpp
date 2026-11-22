#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

class Item {
    int code;
    string name;
    double cost;
    int quantity;
public:
    Item() : code(0), name(""), cost(0.0), quantity(0) {}
    Item(int c, const string &n, double co, int q)
        : code(c), name(n), cost(co), quantity(q) {}

    int getCode() const { return code; }
    const string &getName() const { return name; }
    double getCost() const { return cost; }
    int getQuantity() const { return quantity; }

    void input() {
        cout << "Item Code: ";     cin >> code;
        cin.ignore();
        cout << "Item Name: ";     getline(cin, name);   // names may contain spaces
        cout << "Cost: ";          cin >> cost;
        cout << "Quantity: ";      cin >> quantity;
    }

    void display() const {
        cout << left << setw(10) << code << setw(15) << name
             << setw(12) << fixed << setprecision(2) << cost
             << setw(10) << quantity << "\n";
    }
};

void printHeader() {
    cout << left << setw(10) << "Code" << setw(15) << "Name"
         << setw(12) << "Cost" << setw(10) << "Quantity" << "\n";
    cout << string(47, '-') << "\n";
}

void displayAll(const vector<Item> &items) {
    if (items.empty()) { cout << "No items.\n"; return; }
    printHeader();
    for (const Item &it : items) it.display();
}

int main() {
    vector<Item> items;
    int n;

    cout << "How many items to enter? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for item " << i + 1 << ":\n";
        Item it;
        it.input();
        items.push_back(it);
    }

    int choice;
    do {
        cout << "\n===== Item Menu =====\n"
             << "1. Display items\n"
             << "2. Sort by item code\n"
             << "3. Sort by cost\n"
             << "4. Sort by quantity\n"
             << "5. Search by item code\n"
             << "6. Search by item name\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAll(items);
            break;
        case 2:
            sort(items.begin(), items.end(),
                 [](const Item &a, const Item &b) { return a.getCode() < b.getCode(); });
            cout << "Sorted by item code.\n";
            displayAll(items);
            break;
        case 3:
            sort(items.begin(), items.end(),
                 [](const Item &a, const Item &b) { return a.getCost() < b.getCost(); });
            cout << "Sorted by cost.\n";
            displayAll(items);
            break;
        case 4:
            sort(items.begin(), items.end(),
                 [](const Item &a, const Item &b) { return a.getQuantity() < b.getQuantity(); });
            cout << "Sorted by quantity.\n";
            displayAll(items);
            break;
        case 5: {
            int code;
            cout << "Enter item code to search: ";
            cin >> code;
            auto it = find_if(items.begin(), items.end(),
                              [code](const Item &x) { return x.getCode() == code; });
            if (it != items.end()) {
                cout << "Search result:\n";
                printHeader();
                it->display();
            } else {
                cout << "Item with code " << code << " not found.\n";
            }
            break;
        }
        case 6: {
            string name;
            cout << "Enter item name to search: ";
            getline(cin >> ws, name);
            vector<Item> found;
            for (const Item &x : items)
                if (x.getName() == name) found.push_back(x);
            if (found.empty()) {
                cout << "Item '" << name << "' not found.\n";
            } else {
                cout << "Search results:\n";
                printHeader();
                for (const Item &x : found) x.display();
            }
            break;
        }
        case 0:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
