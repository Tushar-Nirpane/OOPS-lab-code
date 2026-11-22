#include <iostream>
#include <fstream>
using namespace std;

class Student
{
    string name;
    int age, rollno;

public:
    void getdata()
    {
        cout << "Enter student name: ";
        cin >> name;

        cout << "Enter age: ";
        cin >> age;

        cout << "Enter roll number: ";
        cin >> rollno;
    }

    void writefile()
    {
        ofstream fout("student.txt");

        fout << "Student Name: " << name << endl;
        fout << "Age: " << age << endl;
        fout << "Roll Number: " << rollno << endl;

        fout.close();
    }

    void readfile()
    {
        ifstream fin("student.txt");
        string line;

        cout << "\nStudent Details from File:\n";

        while (getline(fin, line))
        {
            cout << line << endl;
        }

        fin.close();
    }
};

int main()
{
    Student s;

    s.getdata();
    s.writefile();
    s.readfile();

    return 0;
}
