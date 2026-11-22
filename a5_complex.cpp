#include <iostream>
using namespace std;

class Complex
{
    int real, imag;

public:

    Complex()
    {
        real = 0;
        imag = 0;
    }

    Complex(int r, int i)
    {
        real = r;
        imag = i;
    }

    Complex operator+(Complex c)
    {
        Complex temp;

        temp.real = real + c.real;
        temp.imag = imag + c.imag;

        return temp;
    }

    Complex operator*(Complex c)
    {
        Complex temp;

        temp.real = (real * c.real) - (imag * c.imag);
        temp.imag = (real * c.imag) + (imag * c.real);

        return temp;
    }

    friend istream& operator>>(istream& in, Complex& c)
    {
        in >> c.real >> c.imag;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Complex& c)
    {
        out << c.real;

        if (c.imag < 0)
            out << " - " << -c.imag;
        else
            out << " + " << c.imag;

        out << "i";
        return out;
    }
};

int main()
{
    Complex c1, c2, c3, c4;

    cout << "Enter first complex number (real imaginary): ";
    cin >> c1;

    cout << "Enter second complex number (real imaginary): ";
    cin >> c2;

    c3 = c1 + c2;
    c4 = c1 * c2;

    cout << "\nFirst Complex Number = " << c1;
    cout << "\nSecond Complex Number = " << c2;

    cout << "\nAddition = " << c3;
    cout << "\nMultiplication = " << c4;

    return 0;
}
