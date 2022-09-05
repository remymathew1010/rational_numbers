#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>

class Rational;
class Integer {

    std::string value;
    char sign;

    bool operator>(const long long&) const;
    bool operator<=(const long long&) const;
    bool operator>=(const long long&) const;
    bool operator!=(const long long&) const;


    // Conversion functions:
    std::string to_string() const;
    int to_int() const;
    long to_long() const;
    long long to_long_long() const;

    // Increment and decrement operators:
    Integer& operator++();       // pre-increment
    Integer& operator--();       // pre-decrement

    friend class Rational;

public:
    // Constructors:
    Integer();
    Integer(const Integer&);
    Integer(const long long&);
    Integer(const std::string&);

    // Assignment operators:
    Integer& operator=(const Integer&);
    Integer& operator=(const std::string&);

    // Unary arithmetic operators:
    Integer operator+() const;   // unary +
    Integer operator-() const;   // unary -

    // Binary arithmetic operators:
    Integer operator+(const Integer&) const;
    Integer operator-(const Integer&) const;
    Integer operator*(const Integer&) const;
    Integer operator/(const Integer&) const;
    Integer operator%(const Integer&) const;

    // Arithmetic-assignment operators:
    Integer& operator+=(const Integer&);
    Integer& operator-=(const Integer&);
    Integer& operator*=(const Integer&);
    Integer& operator/=(const Integer&);
    Integer& operator%=(const Integer&);


    // Relational operators:
    bool operator<(const Integer&) const;
    bool operator>(const Integer&) const;
    bool operator<=(const Integer&) const;
    bool operator>=(const Integer&) const;
    bool operator==(const Integer&) const;
    bool operator!=(const Integer&) const;


    // I/O stream operators:
    friend std::istream& operator>>(std::istream&, Integer&);
    friend std::ostream& operator<<(std::ostream&, const Integer&);

    // helper FUCNTIONS
    bool operator<(const long long&) const;
    bool operator==(const long long&) const;
    Integer operator++(int);     // post-increment
    Integer operator--(int);     // post-decrement

    friend Integer gcd(Integer a, Integer b);
};
#endif INTEGER_H
