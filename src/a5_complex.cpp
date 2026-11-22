#include <iostream>
using namespace std;

class Complex {
    double real, imag;
public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex &o) const { return Complex(real + o.real, imag + o.imag); }
    Complex operator*(const Complex &o) const {
        return Complex(real * o.real - imag * o.imag, real * o.imag + imag * o.real);
    }
    friend ostream &operator<<(ostream &out, const Complex &c) {
        out << c.real << (c.imag < 0 ? " - " : " + ") << (c.imag < 0 ? -c.imag : c.imag) << "i";
        return out;
    }
    friend istream &operator>>(istream &in, Complex &c) {
        cout << "Real part: "; in >> c.real;
        cout << "Imaginary part: "; in >> c.imag;
        return in;
    }
};

int main() {
    Complex zero, a, b;
    cout << "Default complex number: " << zero << "\n";
    cout << "Enter first complex number:\n"; cin >> a;
    cout << "Enter second complex number:\n"; cin >> b;
    cout << "First: " << a << "\nSecond: " << b << "\n";
    cout << "Sum: " << a + b << "\n";
    cout << "Product: " << a * b << "\n";
    return 0;
}
