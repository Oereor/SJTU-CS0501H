#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
    explicit BigInt(const std::string& number);
    BigInt operator+(const BigInt& rhs) const;
    BigInt operator-(const BigInt& rhs) const;
    bool operator>(const BigInt& rhs) const;
    bool operator<(const BigInt& rhs) const;
    bool operator==(const BigInt& rhs) const;
    bool operator!=(const BigInt& rhs) const;
    bool operator>=(const BigInt& rhs) const;
    bool operator<=(const BigInt& rhs) const;
    static BigInt negative(const BigInt& number);
    void output() const;
private:
    BigInt();
    BigInt(int sign, const std::vector<int>& digits);
    void trim();
    std::vector<int> digits;
    int sign;
};

/**
 * Whitespace or commas between digits are safely ignored when parsing.
 * However, prefix whitespaces will not be ignored when parsing a negative number.
 * @param number The string representation of an arbitrarily large integer.
 */
BigInt::BigInt(const std::string& number) {
    if (number[0] == '-') {
        sign = -1;
    }
    else {
        sign = 1;
    }
    for (int i = number.length() - 1; i >= 0; i--) {
        if (int digit = number[i] - '0'; 0 <= digit && digit <= 9) {
            digits.push_back(digit);
        }
    }
}

BigInt::BigInt(const int sign, const std::vector<int>& digits) {
    this->sign = sign;
    for (int digit : digits) {
        this->digits.push_back(digit);
    }
}

BigInt::BigInt() {
    sign = 1;
}

BigInt BigInt::negative(const BigInt &number) {
    BigInt result(-number.sign, number.digits);
    return result;
}

void BigInt::output() const {
    if (sign == -1) {
        std::cout << '-';
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        std::cout << digits[i];
    }
}

BigInt BigInt::operator+(const BigInt &rhs) const {
    BigInt result;
    if (this->sign * rhs.sign == 1) {
        result.sign = this->sign;
        const int len1 = digits.size();
        const int len2 = rhs.digits.size();
        int i = 0, carry = 0;
        for (; i < len1 && i < len2; i++) {
            const int sum = digits[i] + rhs.digits[i] + carry;
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        for (; i < len1; i++) {
            const int sum = digits[i] + carry;
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        for (; i < len2; i++) {
            const int sum = rhs.digits[i] + carry;
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry != 0) {
            result.digits.push_back(carry);
        }
        result.trim();
        return result;
    }

    const BigInt* larger = this->sign == 1 ? this : &rhs;
    const BigInt* smaller = this->sign == -1 ? this : &rhs;
    bool swapped = false;
    if (*larger > negative(*smaller)) {
        result.sign = 1;
    }
    else {
        result.sign = -1;
        const BigInt* lar = new BigInt(1, smaller->digits);
        const BigInt* sma = new BigInt(1, larger->digits);
        swapped = true;
        larger = lar;
        smaller = sma;
    }
    const int largerLen = larger->digits.size();
    const int smallerLen = smaller->digits.size();
    int i = 0, borrow = 0;
    for (; i < largerLen && i < smallerLen; i++) {
        int diff = larger->digits[i] - smaller->digits[i] - borrow;
        borrow = 0;
        if (diff < 0) {
            borrow = 1;
            diff += 10;
        }
        result.digits.push_back(diff);
    }
    for (; i < largerLen; i++) {
        int diff = larger->digits[i] - borrow;
        borrow = 0;
        if (diff < 0) {
            borrow = 1;
            diff += 10;
        }
        result.digits.push_back(diff);
    }
    result.trim();
    if (swapped) {
        delete larger;
        delete smaller;
    }
    return result;
}

BigInt BigInt::operator-(const BigInt &rhs) const {
    return negative(rhs) + *this;
}

bool BigInt::operator>(const BigInt &rhs) const {
    if (this->sign != rhs.sign) {
        return this->sign > rhs.sign;
    }
    if (this->digits.size() != rhs.digits.size()) {
        return this->digits.size() > rhs.digits.size();
    }

    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] * sign > rhs.digits[i] * sign) {
            return true;
        }
    }
    return false;
}

bool BigInt::operator<(const BigInt &rhs) const {
    if (this->sign != rhs.sign) {
        return this->sign < rhs.sign;
    }
    if (this->digits.size() != rhs.digits.size()) {
        return this->digits.size() < rhs.digits.size();
    }

    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] * sign < rhs.digits[i] * sign) {
            return true;
        }
    }
    return false;
}

bool BigInt::operator==(const BigInt &rhs) const {
    if (this->sign != rhs.sign || this->digits.size() != rhs.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != rhs.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt &rhs) const {
    return !(rhs == *this);
}

bool BigInt::operator>=(const BigInt &rhs) const {
    return !(*this < rhs);
}

bool BigInt::operator<=(const BigInt &rhs) const {
    return !(*this > rhs);
}

void BigInt::trim() {
    while (digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.empty()) {
        digits.push_back(0);
        sign = 1;
    }
}

int n;

int* parent;
char* value;

std::vector<int> leafIndex;

std::string currNumStr;

BigInt* result;

void search(int leafIdx) {
    currNumStr = "";
    int curr = leafIdx;
    while (curr != -1) {
        currNumStr.insert(0, 1, value[curr]);
        curr = parent[curr];
    }
    BigInt num(currNumStr);
    *result = *result + num;
}

int main() {
    std::cin >> n;
    parent = new int[n + 1];
    value = new char[n + 1];
    for (int i = 0; i < n + 1; i++) {
        parent[i] = -1;
    }
    for (int i = 1; i <= n; i++) {
        int left, right;
        char val;
        std::cin >> val >> left >> right;
        value[i] = val;
        if (left == 0 && right == 0) {
            leafIndex.push_back(i);
            continue;
        }
        if (left != 0) {
            parent[left] = i;
        }
        if (right != 0) {
            parent[right] = i;
        }
    }
    result = new BigInt("0");
    for (int leaf : leafIndex) {
        search(leaf);
    }
    result->output();
    delete[] parent;
    delete[] value;
    delete result;
    return 0;
}