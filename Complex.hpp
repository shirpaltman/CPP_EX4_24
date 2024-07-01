#include <iostream>
#include <cmath>




/**
 * @class Complex
 * @brief A class to represent and manipulate complex numbers.
 *
 * The Complex class provides functionality for representing complex numbers
 * and performing basic arithmetic operations on them, such as addition, subtraction,
 * multiplication, and division. It also provides methods for accessing and modifying
 * the real and imaginary parts of the complex number.
 *
 * The class supports the following operations:
 * - Construction with default values or specific real and imaginary parts.
 * - Accessing and modifying the real and imaginary parts.
 * - Arithmetic operations: addition, subtraction, multiplication, and division.
 * - Comparison for equality.
 * - Calculating the magnitude (absolute value) of the complex number.
 * - Outputting the complex number to an output stream in a human-readable format.
 *
 * Example usage:
 * @code
 * Complex c1(3.0, 4.0); // Create a complex number 3 + 4i
 * Complex c2(1.0, 2.0); // Create another complex number 1 + 2i
 * Complex sum = c1 + c2; // Perform addition: sum = 4 + 6i
 * Complex diff = c1 - c2; // Perform subtraction: diff = 2 + 2i
 * Complex prod = c1 * c2; // Perform multiplication: prod = -5 + 10i
 * Complex quot = c1 / c2; // Perform division: quot = 2.2 - 0.4i
 * bool isEqual = (c1 == c2); // Check equality: isEqual = false
 * double mag = c1.magnitude(); // Calculate magnitude: mag = 5.0
 * std::cout << c1; // Output: 3 + 4i
 * @endcode
 */
class Complex {
private:
    double real; ///< The real part of the complex number.
    double imag; ///< The imaginary part of the complex number.

public:
    // Constructors
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Getters
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Setters
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }

    // Overloaded addition
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overloaded subtraction
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    /**
     * @brief Overload the multiplication operator.
     * @param other The complex number to multiply.
     * @return The result of the multiplication.
     */
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    /**
     * @brief Overload the division operator.
     * @param other The complex number to divide by.
     * @return The result of the division.
     */

    bool operator==(const Complex& other) const {
        // Consider two Complex numbers equal if their real and imaginary parts are the same
        return real == other.real && imag == other.imag;
    }

    // Magnitude
    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

     /**
     * @brief Overload the output stream operator.
     * @param os The output stream.
     * @param c The complex number to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};