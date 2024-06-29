#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
public:
    double real;  // Real part of the complex number
    double imag;  // Imaginary part of the complex number

    /// @brief Constructor for Complex numbers.
    /// @param r Real part (default is 0.0).
    /// @param i Imaginary part (default is 0.0).
    Complex(double r = 0.0, double i = 0.0);

    /// @brief Overloaded output stream operator to display complex numbers.
    /// @param os Output stream.
    /// @param c Complex number to output.
    /// @return Reference to the output stream.
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    /// @brief Equality operator to compare two complex numbers.
    /// @param other Another complex number to compare with.
    /// @return True if both real and imaginary parts are equal.
    bool operator==(const Complex& other) const;

    /// @brief 
    /// @param other 
    /// @return 
    bool operator<(const Complex& other) const;

};

#endif // COMPLEX_HPP
