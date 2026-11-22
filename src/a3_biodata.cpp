#include <iostream>
#include <string>
using namespace std;

class Base {
protected:
    string name;
    int empID;
public:
    void acceptBase() {
        cout << "Name: ";
        getline(cin >> ws, name);            // full name may contain spaces
        cout << "Employee ID: ";
        cin >> empID;
    }
};

class Personal : virtual public Base {
protected:
    string dob, address;
public:
    void acceptPersonal() { cout << "Date of birth: "; cin >> dob; cout << "Address: "; cin.ignore(); getline(cin, address); }
    void printPersonal() const { cout << "Name: " << name << "\nEmployee ID: " << empID
                                      << "\nDOB: " << dob << "\nAddress: " << address << "\n"; }
};

class Professional : virtual public Base {
protected:
    string designation;
    int experience;
public:
    void acceptProfessional() { cout << "Designation: "; cin >> designation; cout << "Experience (years): "; cin >> experience; }
    void printProfessional() const { cout << "Designation: " << designation << "\nExperience: " << experience << " years\n"; }
};

class Academic : virtual public Base {
protected:
    string degree, university;
    double percentage;
public:
    void acceptAcademic() { cout << "Degree: "; cin >> degree; cout << "University: "; cin >> university; cout << "Percentage: "; cin >> percentage; }
    void printAcademic() const { cout << "Degree: " << degree << "\nUniversity: " << university << "\nPercentage: " << percentage << "\n"; }
};

class BioData : public Personal, public Professional, public Academic {
public:
    void accept() {
        acceptBase();
        if (!cin) return;
        acceptPersonal();
        if (!cin) return;
        acceptProfessional();
        if (!cin) return;
        acceptAcademic();
    }
    void print() const {
        cout << "\n===== EMPLOYEE BIO-DATA =====\n";
        printPersonal();
        printProfessional();
        printAcademic();
    }
};

int main() {
    BioData b;
    b.accept();
    if (!cin) {
        cout << "\nInvalid input: a numeric field received non-numeric text.\n";
        return 1;
    }
    b.print();
    return 0;
}
