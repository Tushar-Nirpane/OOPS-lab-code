#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class CriteriaException : public exception {
    string msg;
public:
    CriteriaException(const string &m) : msg(m) {}
    const char *what() const noexcept override { return msg.c_str(); }
};

void checkUser(int age, double income, const string &city, const string &vehicle) {
    if (age < 18 || age > 55)
        throw CriteriaException("Age must be between 18 and 55.");
    if (income < 50000 || income > 100000)
        throw CriteriaException("Income must be between Rs. 50,000 and Rs. 1,00,000 per month.");
    if (city != "Pune" && city != "Mumbai" && city != "Bangalore" && city != "Chennai")
        throw CriteriaException("City must be Pune, Mumbai, Bangalore or Chennai.");
    if (vehicle != "4-wheeler")
        throw CriteriaException("User must own a 4-wheeler.");
}

int main() {
    int age; double income; string city, vehicle;
    cout << "Age: "; cin >> age;
    cout << "Monthly income (Rs.): "; cin >> income;
    cout << "City: "; cin >> city;
    cout << "Vehicle (4-wheeler / 2-wheeler): "; cin >> vehicle;
    try {
        checkUser(age, income, city, vehicle);
        cout << "All criteria met.\n";
    } catch (const CriteriaException &e) {
        cout << "Criteria not met: " << e.what() << "\n";
    }
    return 0;
}
