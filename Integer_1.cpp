#include <tuple>
#include <string>
#include <climits>
#include <cmath>
#include "Integer.h"

/*
Integer gcd(Integer a, Integer b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
*/


namespace cosc326 {


    bool is_valid_number(const std::string& num) {
        for (char digit : num)
            if (digit < '0' or digit > '9')
                return false;

        return true;
    }



    void strip_leading_zeroes(std::string& num) {
        size_t i;
        for (i = 0; i < num.size(); i++)
            if (num[i] != '0')
                break;

        if (i == num.size())
            num = "0";
        else
            num = num.substr(i);
    }



    void add_leading_zeroes(std::string& num, size_t num_zeroes) {
        num = std::string(num_zeroes, '0') + num;
    }


    void add_trailing_zeroes(std::string& num, size_t num_zeroes) {
        num += std::string(num_zeroes, '0');
    }


    std::tuple<std::string, std::string> get_larger_and_smaller(const std::string& num1,
        const std::string& num2) {
        std::string larger, smaller;
        if (num1.size() > num2.size() or
            (num1.size() == num2.size() and num1 > num2)) {
            larger = num1;
            smaller = num2;
        }
        else {
            larger = num2;
            smaller = num1;
        }

        // pad the smaller number with zeroes
        add_leading_zeroes(smaller, larger.size() - smaller.size());

        return std::make_tuple(larger, smaller);
    }


    // * DEFAULT CONSTRUCTOR
    Integer::Integer() {
        value = "0";
        sign = '+';
    }


    // * COPY CONSTRUCTOR
    Integer::Integer(const Integer& num) {
        value = num.value;
        sign = num.sign;
    }



    Integer::Integer(const long long& num) {
        value = std::to_string(num);
        if (num < 0) {
            sign = '-';
            value = value.substr(1);    // remove minus sign from value
        }
        else
            sign = '+';
    }



    // * STRING CONSTRUCTOR
    Integer::Integer(const std::string& num) {
        if (num[0] == '+' or num[0] == '-') {     // check for sign
            std::string magnitude = num.substr(1);
            if (is_valid_number(magnitude)) {
                value = magnitude;
                sign = num[0];
            }
            else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        else {      // if no sign is specified
            if (is_valid_number(num)) {
                value = num;
                sign = '+';    // positive by default
            }
            else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        strip_leading_zeroes(value);
    }





    std::string Integer::to_string() const {
        // prefix with sign if negative
        return this->sign == '-' ? "-" + this->value : this->value;
    }


    int Integer::to_int() const {
        return std::stoi(this->to_string());
    }



    long Integer::to_long() const {
        return std::stol(this->to_string());
    }




    long long Integer::to_long_long() const {
        return std::stoll(this->to_string());
    }




    // * ASSINGMENT OPERATOR
    Integer& Integer::operator=(const Integer& num) {
        value = num.value;
        sign = num.sign;

        return *this;
    }



    // Integer& Integer::operator=(const long long& num) {
    //     Integer temp(num);
    //     value = temp.value;
    //     sign = temp.sign;

    //     return *this;
    // }



    Integer& Integer::operator=(const std::string& num) {
        Integer temp(num);
        value = temp.value;
        sign = temp.sign;

        return *this;
    }



    // * UNARY OPERATORS

    Integer Integer::operator+() const {
        return *this;
    }



    Integer Integer::operator-() const {
        Integer temp;

        temp.value = value;
        if (value != "0") {
            if (sign == '+')
                temp.sign = '-';
            else
                temp.sign = '+';
        }

        return temp;
    }




    // * REALATIONAL OPERATORS
    bool Integer::operator==(const Integer& num) const {
        return (sign == num.sign) and (value == num.value);
    }



    bool Integer::operator!=(const Integer& num) const {
        return !(*this == num);
    }



    bool Integer::operator<(const Integer& num) const {
        if (sign == num.sign) {
            if (sign == '+') {
                if (value.length() == num.value.length())
                    return value < num.value;
                else
                    return value.length() < num.value.length();
            }
            else
                return -(*this) > -num;
        }
        else
            return sign == '-';
    }



    bool Integer::operator>(const Integer& num) const {
        return !((*this < num) or (*this == num));
    }




    bool Integer::operator<=(const Integer& num) const {
        return (*this < num) or (*this == num);
    }




    bool Integer::operator>=(const Integer& num) const {
        return !(*this < num);
    }




    bool Integer::operator==(const long long& num) const {
        return *this == Integer(num);
    }



    bool operator==(const long long& lhs, const Integer& rhs) {
        return Integer(lhs) == rhs;
    }



    bool Integer::operator!=(const long long& num) const {
        return !(*this == Integer(num));
    }



    bool operator!=(const long long& lhs, const Integer& rhs) {
        return Integer(lhs) != rhs;
    }




    bool Integer::operator<(const long long& num) const {
        return *this < Integer(num);
    }


    bool operator<(const long long& lhs, const Integer& rhs) {
        return Integer(lhs) < rhs;
    }




    bool Integer::operator>(const long long& num) const {
        return *this > Integer(num);
    }



    bool operator>(const long long& lhs, const Integer& rhs) {
        return Integer(lhs) > rhs;
    }



    bool Integer::operator<=(const long long& num) const {
        return !(*this > Integer(num));
    }



    bool operator<=(const long long& lhs, const Integer& rhs) {
        return Integer(lhs) <= rhs;
    }



    bool Integer::operator>=(const long long& num) const {
        return !(*this < Integer(num));
    }



    bool operator>=(const long long& lhs, const Integer& rhs) {
        return Integer(lhs) >= rhs;
    }





    Integer abs(const Integer& num) {
        return num < 0 ? -num : num;
    }




    const long long FLOOR_SQRT_LLONG_MAX = 3037000499;


    // * ARITHMETIC OPERATORS

    Integer Integer::operator+(const Integer& num) const {
        // if the operands are of opposite signs, perform subtraction
        if (this->sign == '+' and num.sign == '-') {
            Integer rhs = num;
            rhs.sign = '+';
            return *this - rhs;
        }
        else if (this->sign == '-' and num.sign == '+') {
            Integer lhs = *this;
            lhs.sign = '+';
            return -(lhs - num);
        }

        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

        Integer result;      // the resultant sum
        result.value = "";  // the value is cleared as the digits will be appended
        short carry = 0, sum;
        // add the two values
        for (long i = larger.size() - 1; i >= 0; i--) {
            sum = larger[i] - '0' + smaller[i] - '0' + carry;
            result.value = std::to_string(sum % 10) + result.value;
            carry = sum / (short)10;
        }
        if (carry)
            result.value = std::to_string(carry) + result.value;

        // if the operands are negative, the result is negative
        if (this->sign == '-' and result.value != "0")
            result.sign = '-';

        return result;
    }



    Integer Integer::operator-(const Integer& num) const {
        // if the operands are of opposite signs, perform addition
        if (this->sign == '+' and num.sign == '-') {
            Integer rhs = num;
            rhs.sign = '+';
            return *this + rhs;
        }
        else if (this->sign == '-' and num.sign == '+') {
            Integer lhs = *this;
            lhs.sign = '+';
            return -(lhs + num);
        }

        Integer result;      // the resultant difference
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        if (abs(*this) > abs(num)) {
            larger = this->value;
            smaller = num.value;

            if (this->sign == '-')      // -larger - -smaller = -result
                result.sign = '-';
        }
        else {
            larger = num.value;
            smaller = this->value;

            if (num.sign == '+')        // smaller - larger = -result
                result.sign = '-';
        }
        // pad the smaller number with zeroes
        add_leading_zeroes(smaller, larger.size() - smaller.size());

        result.value = "";  // the value is cleared as the digits will be appended
        short difference;
        long i, j;
        // subtract the two values
        for (i = larger.size() - 1; i >= 0; i--) {
            difference = larger[i] - smaller[i];
            if (difference < 0) {
                for (j = i - 1; j >= 0; j--) {
                    if (larger[j] != '0') {
                        larger[j]--;    // borrow from the j-th digit
                        break;
                    }
                }
                j++;
                while (j != i) {
                    larger[j] = '9';    // add the borrow and take away 1
                    j++;
                }
                difference += 10;   // add the borrow
            }
            result.value = std::to_string(difference) + result.value;
        }
        strip_leading_zeroes(result.value);

        // if the result is 0, set its sign as +
        if (result.value == "0")
            result.sign = '+';

        return result;
    }




    Integer Integer::operator*(const Integer& num) const {
        if (*this == 0 or num == 0)
            return Integer(0);
        if (*this == 1)
            return num;
        if (num == 1)
            return *this;

        Integer product;
        if (abs(*this) <= FLOOR_SQRT_LLONG_MAX and abs(num) <= FLOOR_SQRT_LLONG_MAX)
            product = std::stoll(this->value) * std::stoll(num.value);
        else {
            // identify the numbers as `larger` and `smaller`
            std::string larger, smaller;
            std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

            size_t half_length = larger.size() / 2;
            auto half_length_ceil = (size_t)ceil(larger.size() / 2.0);

            Integer num1_high, num1_low;
            num1_high = larger.substr(0, half_length);
            num1_low = larger.substr(half_length);

            Integer num2_high, num2_low;
            num2_high = smaller.substr(0, half_length);
            num2_low = smaller.substr(half_length);

            strip_leading_zeroes(num1_high.value);
            strip_leading_zeroes(num1_low.value);
            strip_leading_zeroes(num2_high.value);
            strip_leading_zeroes(num2_low.value);

            Integer prod_high, prod_mid, prod_low;
            prod_high = num1_high * num2_high;
            prod_low = num1_low * num2_low;
            prod_mid = (num1_high + num1_low) * (num2_high + num2_low)
                - prod_high - prod_low;

            add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
            add_trailing_zeroes(prod_mid.value, half_length_ceil);

            strip_leading_zeroes(prod_high.value);
            strip_leading_zeroes(prod_mid.value);
            strip_leading_zeroes(prod_low.value);

            product = prod_high + prod_mid + prod_low;
        }
        strip_leading_zeroes(product.value);

        if (this->sign == num.sign)
            product.sign = '+';
        else
            product.sign = '-';

        return product;
    }



    std::tuple<Integer, Integer> divide(const Integer& dividend, const Integer& divisor) {
        Integer quotient, remainder, temp;

        temp = divisor;
        quotient = 1;
        while (temp < dividend) {
            quotient++;
            temp += divisor;
        }
        if (temp > dividend) {
            quotient--;
            remainder = dividend - (temp - divisor);
        }

        return std::make_tuple(quotient, remainder);
    }



    Integer Integer::operator/(const Integer& num) const {
        Integer abs_dividend = abs(*this);
        Integer abs_divisor = abs(num);

        if (num == 0)
            throw std::logic_error("Attempted division by zero");
        if (abs_dividend < abs_divisor)
            return Integer(0);
        if (num == 1)
            return *this;
        if (num == -1)
            return -(*this);

        Integer quotient;
        if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
            quotient = std::stoll(abs_dividend.value) / std::stoll(abs_divisor.value);
        else if (abs_dividend == abs_divisor)
            quotient = 1;
        else {
            quotient.value = "";    // the value is cleared as digits will be appended
            Integer chunk, chunk_quotient, chunk_remainder;
            size_t chunk_index = 0;
            chunk_remainder.value = abs_dividend.value.substr(chunk_index, abs_divisor.value.size() - 1);
            chunk_index = abs_divisor.value.size() - 1;
            while (chunk_index < abs_dividend.value.size()) {
                chunk.value = chunk_remainder.value.append(1, abs_dividend.value[chunk_index]);
                chunk_index++;
                while (chunk < abs_divisor) {
                    quotient.value += "0";
                    if (chunk_index < abs_dividend.value.size()) {
                        chunk.value.append(1, abs_dividend.value[chunk_index]);
                        chunk_index++;
                    }
                    else
                        break;
                }
                if (chunk == abs_divisor) {
                    quotient.value += "1";
                    chunk_remainder = "0";
                }
                else if (chunk > abs_divisor) {
                    strip_leading_zeroes(chunk.value);
                    std::tie(chunk_quotient, chunk_remainder) = divide(chunk, abs_divisor);
                    quotient.value += chunk_quotient.value;
                }
            }
        }
        strip_leading_zeroes(quotient.value);

        if (this->sign == num.sign)
            quotient.sign = '+';
        else
            quotient.sign = '-';

        return quotient;
    }




    Integer Integer::operator%(const Integer& num) const {
        Integer abs_dividend = abs(*this);
        Integer abs_divisor = abs(num);

        if (abs_divisor == 0)
            throw std::logic_error("Attempted division by zero");
        if (abs_divisor == 1 or abs_divisor == abs_dividend)
            return Integer(0);

        Integer remainder;
        if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
            remainder = std::stoll(abs_dividend.value) % std::stoll(abs_divisor.value);
        else if (abs_dividend < abs_divisor)
            remainder = abs_dividend;
        else {
            Integer quotient = abs_dividend / abs_divisor;
            remainder = abs_dividend - quotient * abs_divisor;
        }
        strip_leading_zeroes(remainder.value);

        // remainder has the same sign as that of the dividend
        remainder.sign = this->sign;
        if (remainder.value == "0")     // except if its zero
            remainder.sign = '+';

        return remainder;
    }

    // * COMPOUND OPERATORS

    Integer& Integer::operator+=(const Integer& num) {
        *this = *this + num;

        return *this;
    }

    Integer& Integer::operator-=(const Integer& num) {
        *this = *this - num;

        return *this;
    }

    Integer& Integer::operator*=(const Integer& num) {
        *this = *this * num;

        return *this;
    }

    Integer& Integer::operator/=(const Integer& num) {
        *this = *this / num;

        return *this;
    }

    Integer& Integer::operator%=(const Integer& num) {
        *this = *this % num;

        return *this;
    }

    Integer& Integer::operator++() {
        *this += 1;

        return *this;
    }

    Integer& Integer::operator--() {
        *this -= 1;

        return *this;
    }

    Integer Integer::operator++(int) {
        Integer temp = *this;
        *this += 1;

        return temp;
    }

    Integer Integer::operator--(int) {
        Integer temp = *this;
        *this -= 1;

        return temp;
    }

    std::istream& operator>>(std::istream& in, Integer& num) {
        std::string input;
        in >> input;
        num = Integer(input);  // remove sign from value and set sign, if exists

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Integer& num) {
        if (num.sign == '-')
            out << num.sign;
        out << num.value;

        return out;
    }

    /*    
    Integer gcd(Integer a, Integer b)
    {
    if (b == 0)
        return a;
    Integer result = a % b;
    return gcd(b, result);
    }
    */

}