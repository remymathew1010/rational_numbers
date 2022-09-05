#include <iostream>
#include "Integer.h"
#include "Rational.h"
using namespace COSC326;

Integer gcd(Integer a, Integer b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void driverOne() {


    string num1 = "10";
    string num2 = "20";
    string num3 = "0";
    Integer i(num1);
    Integer j(num2);
    Integer k(num3);
    Integer l;

    cout << "CHECKING STREAM EXTRACTION operator : " << endl;
    cout << i << endl;
    cout << j << endl;

    k = i;
    cout << "CHECKING ASSINGMENT OPERATOR : " << k << endl;

    cout << "CHECKING + operator : " << (i + j) << endl;
    cout << "CHECKING - operator : " << (i - j) << endl;
    cout << "CHECKING * operator : " << (i * k) << endl;
    cout << "CHECKING / operator : " << (i / k) << endl;
    cout << "CHECKING % operator : " << (i % k) << endl;

    cout << "CHECKING STREAM INSERTION operator : " << endl;
    cout << "Enter NUMBER : ";
    cin >> k;
    cout << k << endl;

    cout << "CHECKING UNARY - : " << -k << endl;
    cout << "CHECKING UNARY + : " << +k << endl;



    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l += i;
    cout << "CHECKING += operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l -= i;
    cout << "CHECKING -= operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l *= i;
    cout << "CHECKING *= operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l /= i;
    cout << "CHECKING /= operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l %= i;
    cout << "CHECKING %= operator : " << l << endl;

    cout << "CHECKING > operator : " << (i > j) << endl;
    cout << "CHECKING < operator : " << (i < j) << endl;
    cout << "CHECKING >= operator : " << (i >= k) << endl;
    cout << "CHECKING <= operator : " << (i <= k) << endl;
    cout << "CHECKING == operator : " << (i == k) << endl;
    cout << "CHECKING != operator : " << (i != k) << endl;

    i = 105;
    j = 30;
    cout << "GCD calculator CHECKING for (105,30): " << gcd(i, j);
    cout << endl;


}


void driverTwo() {
    Rational r1, r2, l, i;

    // * STREAM INSERTION
    cin >> r1;
    cin >> r2;

    // * STREAM EXTRACTION
    cout << r1 << endl;
    cout << r2 << endl;

    Rational k = r1;
    cout << "CHECKING ASSINGMENT OPERATOR : " << k << endl;

    cout << "CHECKING + operator : " << (r1 + r2) << endl;
    cout << "CHECKING - operator : " << (r1 - r2) << endl;
    cout << "CHECKING * operator : " << (r1 * r2) << endl;
    cout << "CHECKING / operator : " << (r1 / r2) << endl;

    cout << "CHECKING STREAM INSERTION operator : " << endl;
    cout << "Enter K : ";
    cin >> k;
    cout << k << endl;

    cout << "CHECKING UNARY - : " << -k << endl;
    cout << "CHECKING UNARY + : " << +k << endl;

    cout << "Enter I : ";
    cin >> i;

    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l += i;
    cout << "CHECKING += operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l -= i;
    cout << "CHECKING -= operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l *= i;
    cout << "CHECKING *= operator : " << l << endl;


    l = k;
    cout << "L is : " << l << endl;
    cout << "I is : " << i << endl;
    l /= i;
    cout << "CHECKING /= operator : " << l << endl;



    cout << "CHECKING > operator : " << (i > k) << endl;
    cout << "CHECKING < operator : " << (i < k) << endl;
    cout << "CHECKING >= operator : " << (i >= k) << endl;
    cout << "CHECKING <= operator : " << (i <= k) << endl;
    cout << "CHECKING == operator : " << (i == k) << endl;
    cout << "CHECKING != operator : " << (i != k) << endl;


}

int main() {


    driverOne();
    // driverTwo();


    return 0;
}