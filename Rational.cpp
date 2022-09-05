#include <string>
#include "Integer.h"
#include "Rational.h"

using namespace COSC326;
Integer findGCD(Integer a, Integer b)
{
    if (b == 0)
        return a;
    return findGCD(b, a % b);
}
void lowestFraction(Integer& num1, Integer& num2)
{
    Integer denom;
    denom = gcd(num1, num2);
    num1 /= denom;
    num2 /= denom;
}

Rational::Rational() {
    whole = "0";
    numerator = "0";
    denominator = "1";
    sign = '+';
}


// * ARGUMENTED CONSTRUCTOR
Rational::Rational(Integer a) {
    whole = a;
    numerator = "0";
    denominator = "1";
    sign = '+';
}

Rational::Rational(Integer a, Integer b) {
    whole = "0";
    numerator = a;
    if (b > 0)
        denominator = b;
    else
        denominator = "1";
    sign = '+';
}


Rational::Rational(Integer a, Integer b, Integer c) {
    whole = a;
    numerator = b;
    if (c > 0)
        denominator = c;
    else
        denominator = "1";
    sign = '+';
}


// * COPY CONSTRUCTOR
Rational::Rational(const Rational& num) {
    whole = num.whole;
    numerator = num.numerator;
    denominator = num.denominator;
    sign = num.sign;
}





// * STRING CONSTRUCTOR
Rational::Rational(const std::string& input) {

    int locationOfSlash = input.find("/");
    int locationOfDot = input.find(".");
    int numberOfDotsFound = 0;

    if (locationOfDot != -1) {
        if (locationOfDot < locationOfSlash) {
            numberOfDotsFound = locationOfSlash - locationOfDot - 1;
        }
    }

    if (locationOfSlash != -1) {

        string a;

        if (a[0] == '+' || a[0] == '-') {
            sign = a[0];
            a = input.substr(1, locationOfSlash - 1);
        }
        else {
            sign = '+';
            a = input.substr(0, locationOfSlash);
        }

        float value = stof(a);
        int i = numberOfDotsFound;
        while (i > 0) {
            value *= 10;
            i--;
        }
        i = (int)value;
        a = to_string(i);

        // cout<<a<<endl;
        string b = input.substr(locationOfSlash + 1);
        // cout<<b<<endl;

        numerator = a;
        denominator = b;
        while (numberOfDotsFound > 0) {
            denominator *= 10;
            numberOfDotsFound--;
        }
        // cout<<num.denominator;

    }
    else {
        string a = input.substr(0, locationOfSlash);
        numerator = a;
        denominator = 1;
    }

    reducer();

}





// * ASSINGMENT OPERATOR
Rational& Rational::operator=(const Rational& num) {
    whole = num.whole;
    numerator = num.numerator;
    denominator = num.denominator;
    sign = num.sign;

    return *this;
}



// * UNARY OPERATORS

Rational Rational::operator+() const {
    return *this;
}



Rational Rational::operator-() const {
    Rational temp = *this;

    if (whole != 0) {
        if (sign == '+')
            temp.sign = '-';
        else
            temp.sign = '+';
    }

    return temp;
}




// * REALATIONAL OPERATORS
bool Rational::operator==(const Rational& num) const {
    return (sign == num.sign) && (whole == num.whole) && (numerator == num.numerator) && (denominator == num.denominator);
}



bool Rational::operator!=(const Rational& num) const {
    return !(*this == num);
}



bool Rational::operator<(const Rational& num) const {

    if (sign == num.sign) {

        if (whole < num.whole) {
            return true;
        }
        else if (whole == num.whole) {
            if (numerator * num.denominator < denominator * num.numerator) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }

    }
    else {
        if (sign == '-' && num.sign == '+') {
            return true;
        }
        else {
            return false;
        }
    }

}



bool Rational::operator>(const Rational& num) const {
    return !((*this < num) or (*this == num));
}




bool Rational::operator<=(const Rational& num) const {
    return (*this < num) or (*this == num);
}




bool Rational::operator>=(const Rational& num) const {
    return !(*this < num);
}






// * ARITHMETIC OPERATORS

Rational Rational::operator+(const Rational& num) const {

    Rational temp;

    Integer zero;

    Integer tempANumerator;
    Integer tempBNumerator;
    if (whole == zero) {
        tempANumerator = numerator;
    }
    else {
        tempANumerator = whole * numerator;
    }
    if (num.whole == zero) {
        tempBNumerator = num.numerator;
    }
    else {
        tempBNumerator = num.whole * num.numerator;
    }
    temp.whole = "0";

    // if the operands are of opposite signs, perform subtraction
    if (this->sign == num.sign) {

        if (denominator == num.denominator) {
            temp.denominator = denominator;
            temp.numerator = tempANumerator + tempBNumerator;
        }
        else {
            temp.numerator = denominator * num.denominator;
            temp.denominator = tempANumerator * num.denominator + tempBNumerator * denominator;
        }

        temp.sign = num.sign;

    }
    else {

        if (this->sign == '-') {

            if (denominator == num.denominator) {
                temp.denominator = denominator;
                temp.numerator = (-tempANumerator) + tempBNumerator;
            }
            else {
                temp.numerator = denominator * num.denominator;
                temp.denominator = (-(tempANumerator * num.denominator)) + tempBNumerator * denominator;
            }

            if (temp.numerator.sign == '-' || temp.denominator.sign == '-') {
                temp.sign = '-';
            }
            else {
                temp.sign = '+';
            }

        }
        else if (num.sign == '-') {

            if (denominator == num.denominator) {
                temp.denominator = denominator;
                temp.numerator = tempANumerator + (-tempBNumerator);
            }
            else {
                temp.numerator = denominator * num.denominator;
                temp.denominator = tempANumerator * num.denominator + (-(tempBNumerator * denominator));
            }

            if (temp.numerator.sign == '-' || temp.denominator.sign == '-') {
                temp.sign = '-';
            }
            else {
                temp.sign = '+';
            }

        }


    }

    temp.reducer();


    return temp;
}



Rational Rational::operator-(const Rational& num) const {
    return *this + num;
}




Rational Rational::operator*(const Rational& num) const {

    Rational temp;

    Integer zero;
    Integer one("1");
    Integer tempANumerator;
    Integer tempBNumerator;

    if (whole == zero) {
        if (numerator == zero) {
            tempANumerator = one;
        }
        else {
            tempANumerator = numerator;
        }
    }
    else {
        if (numerator == zero) {
            tempANumerator = whole;
        }
        else {
            tempANumerator = whole * numerator;
        }
    }

    if (num.whole == zero) {
        if (numerator == zero) {
            tempBNumerator = one;
        }
        else {
            tempBNumerator = num.numerator;
        }
    }
    else {
        if (num.numerator == zero) {
            tempBNumerator = num.whole;
        }
        else {
            tempBNumerator = num.whole * num.numerator;
        }
    }

    // temp.whole = "0";
    // cout<<endl;
    // cout<<tempANumerator<<endl;
    // cout<<tempBNumerator<<endl;
    // cout<<denominator<<endl;
    // cout<<num.denominator<<endl;
    temp.numerator = tempANumerator * tempBNumerator;
    temp.denominator = denominator * num.denominator;

    temp.reducer();

    if (sign == num.sign) {
        temp.sign = '+';
    }
    else {
        temp.sign = '-';
    }

    return temp;
}



Rational Rational::operator/(const Rational& num) const {

    Rational temp;

    Integer tempANumerator = whole * numerator;
    Integer tempBNumerator = num.whole * num.numerator;
    temp.whole = "0";

    temp.numerator = tempANumerator * num.denominator;
    temp.denominator = denominator * tempBNumerator;

    temp.reducer();

    if (sign == num.sign) {
        temp.sign = '+';
    }
    else {
        temp.sign = '-';
    }

    return temp;
}


// * COMPOUND OPERATORS

Rational& Rational::operator+=(const Rational& num) {
    *this = *this + num;
    this->reducer();
    return *this;
}




Rational& Rational::operator-=(const Rational& num) {
    *this = *this - num;
    this->reducer();
    return *this;
}



Rational& Rational::operator*=(const Rational& num) {
    *this = *this * num;
    this->reducer();
    return *this;
}



Rational& Rational::operator/=(const Rational& num) {
    *this = *this / num;
    this->reducer();
    return *this;
}





std::istream& operator>>(std::istream& in, Rational& num) {
    std::string input;
    in >> input;

    int locationOfSlash = input.find("/");
    int locationOfDot = input.find(".");
    int numberOfDotsFound = 0;

    if (locationOfDot != -1) {
        if (locationOfDot < locationOfSlash) {
            numberOfDotsFound = locationOfSlash - locationOfDot - 1;
        }
    }

    if (locationOfSlash != -1) {

        string a;

        if (a[0] == '+' || a[0] == '-') {
            num.sign = a[0];
            a = input.substr(1, locationOfSlash - 1);
        }
        else {
            num.sign = '+';
            a = input.substr(0, locationOfSlash);
        }

        float value = stof(a);
        int i = numberOfDotsFound;
        while (i > 0) {
            value *= 10;
            i--;
        }
        i = (int)value;
        a = to_string(i);

        // cout<<a<<endl;
        string b = input.substr(locationOfSlash + 1);
        // cout<<b<<endl;

        num.numerator = a;
        num.denominator = b;
        while (numberOfDotsFound > 0) {
            num.denominator *= 10;
            numberOfDotsFound--;
        }
        // cout<<num.denominator;

    }
    else {
        string a = input.substr(0, locationOfSlash);
        num.numerator = a;
        num.denominator = 1;
    }

    num.reducer();

    return in;
}



std::ostream& operator<<(std::ostream& out, const Rational& num) {

    Integer temp1 = 0;

    if (num.sign == '-')
        out << num.sign;

    if (num.whole != temp1) {
        out << num.whole << " ";
    }
    if (num.numerator != temp1) {
        out << num.numerator;
        out << "/";
        out << num.denominator;
    }

    // out<<num.whole<<" ";
    // out << num.numerator;
    // out << "/";
    // out << num.denominator;

    return out;
}





void Rational::reducer() {
    if (numerator < denominator) {

    }
    else if (numerator == denominator) {
        whole = "1";
        numerator = "0";
        denominator = "1";
    }
    else {
        while (numerator >= denominator) {
            numerator -= denominator;
            whole++;
        }
    }
}



