#include "Complex.hpp"

Complex::Complex(double r, double i) : real(r), imag(i) {}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << ", " << c.imag << ")";
    return os;
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator<(const Complex& other) const {
    return real < other.real || (real == other.real && imag < other.imag);
}
