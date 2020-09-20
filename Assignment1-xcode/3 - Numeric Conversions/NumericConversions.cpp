/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <cmath>
#include "console.h"

using namespace std;


/* Function prototypes */

int stringToIntImpl(string str, int exponent);
int charToDigit(char chr);
int stringToInt(string str);
int stringToIntImpl2(string str, int oom);
int stringToInt2(string str);
int sign(string str);
string abs(string str);

int head(int n);
int tail(int n);
char digitToChar(int digit);

string intToString(int n);
string intToStringImpl(int n);


int main() {
    cout << "inToString(-100): " << intToString(-100L) << endl;
    cout << "inToString(29): " << intToString(29L) << endl;
    cout << "inToString(0): " << intToString(0L) << endl;
    cout << endl;
    cout << "stringToInt(\"29\"): " << stringToInt("29") << endl;
    cout << "stringToInt(\"10\"): " << stringToInt("10") << endl;
    cout << "stringToInt(\"-5\"): " << stringToInt("-5") << endl;
    cout << endl;
    cout << "stringToInt2(\"29\"): " << stringToInt2("29") << endl;
    cout << "stringToInt2(\"10\"): " << stringToInt2("10") << endl;
    cout << "stringToInt2(\"-5\"): " << stringToInt2("-5") << endl;
    return 0;
}


/* Function stringToInt Version 2
 
 Improvement of Version 1.
 Does not need to establish order of magnitude.
 Deals with negative/positive cases the same.
 Creates order of magnitude more naturally and does not rely on cmath::pow.
*/
int stringToInt2(string str) {
    return sign(str) * stringToIntImpl2(abs(str), 1);
}

int stringToIntImpl2(string str, int oom) {
    if (str.empty()) return 0;
    return charToDigit(str.back()) * oom + stringToIntImpl2(str.substr(0, str.length() - 1), oom * 10);
}

int sign(string str) {
    return (str.front() == '-') ? -1 : 1;
}

string abs(string str) {
    return (str.front() == '-') ? str.substr(1, str.length()) : str;
}


/* Function stringToInt Version 1
Establishes order of magnitude and recursively calls with smaller oom
 each time.
Deals with negative/positive cases differently.
 */
int stringToInt(string str) {
    // Negative case
    if (str[0] == '-') {
        int order = str.length() - 2;
        return -1 * stringToIntImpl(str.substr(1, str.length()), order);
    } else {
    // Positive case
        int order = str.length() - 1;
        return stringToIntImpl(str, order);
    }
}

int stringToIntImpl(string str, int exponent) {
    
    if (str.length() == 1) {
        return charToDigit(str[0]) * pow(10, exponent);
    } else {
        return charToDigit(str[0]) * pow(10, exponent) + stringToIntImpl(str.substr(1, str.length()), exponent - 1);
    }
}


int charToDigit(char chr) {
    return(chr - '0');
}


/* Function intToString
 */
string intToString(int n) {
    if (n == 0) return "0";
    if (n < 0) {
        return "-" + intToStringImpl(-n);
    } else {
        return intToStringImpl(n);
    }
    
}

string intToStringImpl(int n) {
    if (n == 0) {
        return "";
    } else {
        return(intToStringImpl(tail(n)) + digitToChar(head(n)));
    }
}

int head(int n) {
    return n % 10;
}

int tail(int n) {
    return n / 10;
}

char digitToChar(int digit) {
    return(char(digit + '0'));
}
