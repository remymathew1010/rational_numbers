#ifndef RATIONAL_H
#define RATIONAL_H

class Rational
{

    Integer whole;
    Integer numerator;
    Integer denominator;
    char sign;


    void reducer();


public:
    // Constructors:
    Rational();
    Rational(Integer);
    Rational(Integer, Integer);
    Rational(Integer, Integer, Integer);
    Rational(const Rational&);
    Rational(const std::string&);

    // Assignment operators:
    Rational& operator=(const Rational&);

    // Unary arithmetic operators:
    Rational operator+() const;   // unary +
    Rational operator-() const;   // unary -

    // Binary arithmetic operators:
    Rational operator+(const Rational&) const;
    Rational operator-(const Rational&) const;
    Rational operator*(const Rational&) const;
    Rational operator/(const Rational&) const;

    // Arithmetic-assignment operators:
    Rational& operator+=(const Rational&);
    Rational& operator-=(const Rational&);
    Rational& operator*=(const Rational&);
    Rational& operator/=(const Rational&);



    // Relational operators:
    bool operator<(const Rational&) const;
    bool operator>(const Rational&) const;
    bool operator<=(const Rational&) const;
    bool operator>=(const Rational&) const;
    bool operator==(const Rational&) const;
    bool operator!=(const Rational&) const;


    // I/O stream operators:
    friend std::istream& operator>>(std::istream&, Rational&);
    friend std::ostream& operator<<(std::ostream&, const Rational&);

    // helper FUCNTIONS
    //bool operator<(const long long&) const;
    //bool operator==(const long long&) const;

};

#endif // !RATIONAL_H
