#pragma once

#include <iostream>
#include <vector>

class BigInt {
public:
    std::vector<unsigned int>digits;
    unsigned int length{};
    explicit BigInt(std::string num) {
        if(num[0] == '0' && num.length() > 1)
            throw std::invalid_argument("The first digit cannot be zero!");
        for(char i : num)
            digits.push_back((i - '0'));
        length = num.length();
     }
     explicit BigInt(std::vector<unsigned int> digits) {
         if(digits[0] == 0 && digits.size() > 1)
             throw std::invalid_argument("The first digit cannot be zero!");
        this->digits = digits;
        length = digits.size();
    }
    unsigned int &operator [](unsigned int index) {
        return digits[index];
    }

    friend BigInt operator+(BigInt num1, BigInt num2);

    friend BigInt operator-(BigInt num1, BigInt num2);

    friend BigInt operator*(BigInt num1, BigInt num2);

    friend bool operator<(BigInt num1, BigInt num2);

    friend bool operator>(BigInt num1, BigInt num2);

    friend bool operator==(BigInt num1, BigInt num2);

    friend BigInt operator/(BigInt num1, int divisor);

    friend int operator%(BigInt num1, int num2);

    static bool Is_perfect(BigInt n);

    static std::string To_string(BigInt num);

    static BigInt Square_root(BigInt num);


};



