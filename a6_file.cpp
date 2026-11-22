#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const char *fname = "students.txt";
    int n;
    ofstream out(fname);
    if (!out) { cout << "Cannot open file for writing.\n"; return 1; }
    cout << "How many students? "; cin >> n;
    for (int i = 0; i < n; i++) {
        string name; int age, roll;
        cout << "Name, age, roll number: "; cin >> name >> age >> roll;
        out << left << setw(20) << name << setw(6) << age << setw(10) << roll << "\n";
    }
    out.close();
    cout << "Data written and file closed.\n";

    ifstream in(fname);
    if (!in) { cout << "Cannot open file for reading.\n"; return 1; }
    cout << "\n" << left << setw(20) << "Name" << setw(6) << "Age" << setw(10) << "Roll" << "\n";
    cout << string(36, '-') << "\n";
    string name; int age, roll;
    while (in >> name >> age >> roll)
        cout << left << setw(20) << name << setw(6) << age << setw(10) << roll << "\n";
    in.close();
    return 0;
}
