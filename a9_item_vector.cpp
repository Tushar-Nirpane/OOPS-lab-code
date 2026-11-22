#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Item {
public:
    int code, quantity;
    string name;
    float cost;

    void input() {
        cout << "Enter Code, Name, Cost, Quantity: ";
        cin >> code >> name >> cost >> quantity;
    }

    void display() const {
        cout << code << "\t" << name << "\t"
             << cost << "\t" << quantity << endl;
    }
};

int main() {
    vector<Item> v;
    int ch, n, code;
    string name;

    do {
        cout << "\n1. Add Items";
        cout << "\n2. Sort by Code";
        cout << "\n3. Sort by Cost";
        cout << "\n4. Sort by Quantity";
        cout << "\n5. Search by Code";
        cout << "\n6. Search by Name";
        cout << "\n7. Display Items";
        cout << "\n8. Exit";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch(ch) {
        case 1:
            cout << "Enter number of items: ";
            cin >> n;
            for(int i = 0; i < n; i++) {
                Item x;
                x.input();
                v.push_back(x);
            }
            break;

        case 2:
            sort(v.begin(), v.end(),
                 [](Item a, Item b) {
                     return a.code < b.code;
                 });
            cout << "Sorted by Code!\n";
            break;

        case 3:
            sort(v.begin(), v.end(),
                 [](Item a, Item b) {
                     return a.cost < b.cost;
                 });
            cout << "Sorted by Cost!\n";
            break;

        case 4:
            sort(v.begin(), v.end(),
                 [](Item a, Item b) {
                     return a.quantity < b.quantity;
                 });
            cout << "Sorted by Quantity!\n";
            break;

        case 5:
            cout << "Enter item code: ";
            cin >> code;
            {
                auto it = find_if(v.begin(), v.end(),
                                  [code](Item a) {
                                      return a.code == code;
                                  });

                if(it != v.end())
                    it->display();
                else
                    cout << "Item not found!\n";
            }
            break;

        case 6:
            cout << "Enter item name: ";
            cin >> name;
            {
                auto it = find_if(v.begin(), v.end(),
                                  [name](Item a) {
                                      return a.name == name;
                                  });

                if(it != v.end())
                    it->display();
                else
                    cout << "Item not found!\n";
            }
            break;

        case 7:
            cout << "\nCode\tName\tCost\tQuantity\n";
            for(auto x : v)
                x.display();
            break;

        case 8:
            cout << "Exiting...";
            break;

        default:
            cout << "Invalid choice!";
        }

    } while(ch != 8);

    return 0;
}
