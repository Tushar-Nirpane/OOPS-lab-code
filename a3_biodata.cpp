#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    int empId;
    string name;

public:
    void getPersonData() {
        cout << "Enter Employee ID: ";
        cin >> empId;
        cout << "Enter Name: ";
        cin >> name;
    }

    void displayPersonData() {
        cout << "Employee ID : " << empId << endl;
        cout << "Name        : " << name << endl;
    }
};

class PersonalRecord : virtual public Person {
protected:
    string phone;
    string city;

public:
    void getPersonalData() {
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "\nEnter City: ";
        cin >> city;
    }

    void displayPersonalData() {
        cout << "Phone : " << phone << endl;
        cout << "City  : " << city << endl;
    }
};

class ProfessionalRecord : virtual public Person {
protected:
    string designation;
    double salary;

public:
    void getProfessionalData() {
        cout << "Enter Designation: ";
        cin >> designation;
        cout << "Enter Salary: ";
        cin >> salary;
    }

    void displayProfessionalData() {
        cout << "Designation : " << designation << endl;
        cout << "Salary      : " << salary << endl;
    }
};

class AcademicRecord : public PersonalRecord, public ProfessionalRecord {
private:
    string degree;
    float marks;

public:
    void acceptBioData() {
        cout << "--- Enter Employee Bio-Data ---" << endl;
        getPersonData();
        getPersonalData();
        getProfessionalData();

        cout << "Enter Highest Degree: ";
        cin >> degree;
        cout << "Enter Percentage/Marks: ";
        cin >> marks;
    }

    void printBioData() {
        cout << "\n===============================" << endl;
        cout << "          EMPLOYEE BIO-DATA       " << endl;
        cout << "===============================" << endl;

        displayPersonData();
        displayPersonalData();
        displayProfessionalData();

        cout << "Degree     : " << degree << endl;
        cout << "Marks/CGPA : " << marks << endl;
        cout << "===============================" << endl;
    }
};

int main() {
    AcademicRecord emp;

    emp.acceptBioData();
    emp.printBioData();

    return 0;
}
