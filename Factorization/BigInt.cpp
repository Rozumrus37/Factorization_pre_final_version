#include "BigInt.h"
#include <vector>

int operator%(BigInt num, int num2) {
    int res = 0;
    for (int i = 0; i < num.length; i++)
        res = (res*10 + (int)num[i] - '0') % num2;
    return res;
}

bool operator>(BigInt num1, BigInt num2) {
    if(num1.length > num2.length)
        return 1;

    if(num2.length > num1.length)
        return 0;

    for(int i = 0; i < num1.length; i++) {
        if(num1[i] > num2[i]) return 1;
        else if(num1[i] < num2[i]) return 0;
    }
    return 0;
}
BigInt operator+(BigInt num1, BigInt num2) {
    BigInt number1 = num1.length > num2.length ? num1 : num2;
    BigInt number2 = num1.length <= num2.length ? num1 : num2;
    int carry = 0;
    std::vector<unsigned int>result(10000);
    int j = number2.length-1;
    for(int i = number1.length-1; i >= 0; i--){
        uint sum = 0;
        if(j >= 0)
            sum = number1[i] + number2[j] + carry;
        else
            sum = number1[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
        j--;
    }
    BigInt Result(result);
    if(carry != 0) {
        result[number1.length] = carry;
        Result.length = number1.length+1;
    } else {
        Result.length = number1.length;
    }

    return Result;
}

BigInt operator/(BigInt num1, int divisor) {
    if(divisor == 0) {
        throw std::invalid_argument("Divide by zero is impossible!!!");
    }
    std::vector<unsigned int> answer(1000, 0);
    int idx = 0;
    int temp = num1[idx];
    int j = 0;
    while (temp < divisor)
        temp = temp * 10 + num1[++idx];
    while (num1.length > idx) {
        answer[j] = (temp / divisor);
        temp = (temp % divisor) * 10 + num1[++idx];
        j++;
    }
    BigInt res(answer);
    if (j == 0) {
        res.length = 1;
        return res;
    }
    res.length = j;
    return res;
}

BigInt operator-(BigInt num1, BigInt num2) {
    BigInt number1 = num1 > num2 ? num1 : num2;
    BigInt number2 = num1 < num2 || num1 == num2 ? num1 : num2;
    if(number1 == number2) {
        BigInt res("0");
        return res;
    }

    for(int i = number1.length-1; i >= number1.length/2 && number1.length > 1; i--)
        std::swap(number1[i], number1[number1.length-1-i]);

    for(int i = number2.length-1; i >= number2.length/2 && number2.length > 1; i--)
        std::swap(number2[i], number2[number2.length-1-i]);

    std::vector<unsigned int> res(1000);

    int carry = 0;

    for(int i = 0; i < number2.length; i++) {
        int sub;
        if(number1.length != number2.length || number1.length == number2.length)
            sub = number1[i] - number2[i] - carry;
        else
            sub = number2[i] - number1[i] - carry;
        if(sub < 0) {
            sub += 10;
            carry = 1;
        } else
            carry = 0;
        res[i] = sub;
    }

    for (int i = number2.length; i < number1.length; i++) {
        int sub = number1[i] - carry;
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else
            carry = 0;
        res[i] = sub;
    }

    for(int i = number1.length-1; i >= number1.length/2 && number1.length > 1; i--)
        std::swap(res[i], res[number1.length-1-i]);

    std::string ans = "";
    int len = number1.length;
    bool m = 0;
    if(res[0] == 0) {
        for (int i = 0; i < number1.length; i++) {
            if(!m) len--;
            if (res[i] == 0 && res[i + 1] != 0 && !m) {
                m = 1;
            } else if (m) ans += res[i] + '0';
        }
    }
    if(m == 0) {
        BigInt result(res);
        result.length = number1.length;
        return result;
    }
    BigInt result(ans);
    result.length = len;
    return result;
}

BigInt operator*(BigInt num1, BigInt num2) {
    BigInt number1 = num1.length > num2.length ? num1 : num2;
    BigInt number2 = num1.length <= num2.length ? num1 : num2;
    std::vector<unsigned int> num_arr(10000, 0);
    BigInt result(num_arr);
    if(number1[0] == 0 || number2[0] == 0) {
        result.length = 1;
        return result;
    }
    for(int i = number1.length-1; i >= number1.length/2 && number1.length > 1; i--)
        std::swap(number1[i], number1[number1.length-1-i]);

    for(int i = number2.length-1; i >= number2.length/2 && number2.length > 1; i--)
        std::swap(number2[i], number2[number2.length-1-i]);

    for(int i = 0; i < number2.length; i++)
        for(int j = 0; j < number1.length; j++)
            result[i + j] += number2[i] * number1[j];

    for(int i = 0; i < number1.length + number2.length; i++) {
        int t = result[i]/10;
        result[i] = result[i] % 10;
        result[i+1] = result[i+1] + t;
    }
    result.length = number1.length + number2.length;
    int i;
    for(i = number1.length + number2.length; i >= 0; i--) {
        if(result[i] > 0)
            break;
    }
    result.length = i+1;
    for(i = result.length-1; i >= result.length/2; i--)
        std::swap(result[i], result[result.length-1-i]);

    return result;
}

bool operator<(BigInt num1, BigInt num2) {
    if(num1.length < num2.length)
        return 1;

    if(num2.length < num1.length)
        return 0;

    for(int i = 0; i < num1.length; i++) {
        if(num1[i] < num2[i]) return 1;
        else if(num1[i] > num2[i]) return 0;
    }
    return 0;
}

bool operator == (BigInt num1, BigInt num2) {
    if(num1.length == num2.length) {
        for(int i = 0; i < num1.length; i++)
        if(num1[i] != num2[i])
            return 0;
        return 1;
    }
    return 0;
}

std::string BigInt::To_string(BigInt num) {
    std::string result = "";
    for(int i = 0; i < num.length; i++)
        result += num[i] + '0';
    return result;
}

BigInt BigInt::Square_root(BigInt num) {
    BigInt l("0"), r(To_string(num)), mid("0"), one("1"), ans("0");
    while (l < r || l == r) {
        mid = (l + r) / 2;
        BigInt mid_pow = mid * mid;
        if (mid_pow == num) {
            return mid;
        }
        if(mid_pow < num) {
            l = mid + one;
            ans = mid;
        } else
            r = mid - one;

    }
    return ans;
}



bool BigInt::Is_perfect(BigInt n) {
    if(BigInt::Square_root(n) * BigInt::Square_root(n) == n)
        return 1;
    return 0;
}


