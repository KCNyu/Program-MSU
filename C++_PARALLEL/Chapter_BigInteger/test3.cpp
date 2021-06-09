﻿
#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>
#include <stdlib.h>
#include <execution>
#include <ppl.h>
//#include "BigInteger.h"

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

const int iterationCount = 5;
const size_t testSize = 10;

class BigInteger {
private:
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    // Each vector contains eight digits
    bool sign;
    // false means negative
    size_t length;
    // length of digits
    std::vector<int> num;
    // reverse storage
public:
    // Constructor
    BigInteger(long long x = 0) { *this = x; }
    BigInteger(const std::string& x) { *this = x; }
    BigInteger(const BigInteger& x) { *this = x; }

    // cut Zero prefix
    void cutLeadingZero() {
        while (num.back() == 0 && num.size() != 1) { num.pop_back(); }
    }

    // set the length
    void setLength() {
        cutLeadingZero();
        int tmp = num.back();
        if (tmp == 0) { length = 1; }
        else {
            length = (num.size() - 1) * WIDTH;
            while (tmp > 0) {
                ++length;
                tmp /= 10;
            }
        }
    }

    BigInteger& operator=(long long x) {
        num.clear();
        if (x >= 0) sign = true;
        else {
            sign = false;
            x = -x;
        }
        do {
            num.emplace_back(x % BASE);
            x /= BASE;
        } while (x > 0);
        setLength();
        return *this;
    }

    BigInteger& operator=(const std::string& str) {
        num.clear();
        sign = (str[0] != '-');//设置符号
        int x, len = (str.size() - 1 - (!sign)) / WIDTH + 1;
        for (int i = 0; i < len; i++) {
            int End = str.length() - i * WIDTH;
            int start = std::max((int)(!sign), End - WIDTH);//防止越界
            sscanf_s(str.substr(start, End - start).c_str(), "%d", &x);
            num.push_back(x);
        }
        setLength();
        return *this;
    }

    BigInteger& operator=(const BigInteger& tmp) {
        num = tmp.num;
        sign = tmp.sign;
        length = tmp.length;
        return *this;
    }


    size_t size() const { return length; }

    // get 10^n
    BigInteger e(size_t n) const {
        int tmp = n % WIDTH;
        BigInteger ans;
        ans.length = n + 1;
        n /= WIDTH;
        while (ans.num.size() <= n) ans.num.push_back(0);
        ans.num[n] = 1;
        while (tmp--) ans.num[n] *= 10;
        return ans * (*this);
    }

    // absolute
    BigInteger abs() const {
        BigInteger ans(*this);
        ans.sign = true;
        return ans;
    }

    const BigInteger& operator+() const { return *this; }

    BigInteger operator+(const BigInteger& b) const {
        if (!b.sign) { return *this - (-b); }
        if (!sign) { return b - (-*this); }
        BigInteger ans;
        ans.num.clear();
        for (int i = 0, g = 0;; i++) {
            int sz = static_cast<int>(num.size());
            int b_sz = static_cast<int>(b.num.size());
            if (g == 0 && i >= sz && i >= b_sz) break;
            int x = g;
            if (i < sz) x += num[i];
            if (i < b_sz) x += b.num[i];
            ans.num.push_back(x % BASE);
            g = x / BASE;
        }
        ans.setLength();
        return ans;
    }

    BigInteger operator-() const {
        BigInteger ans(*this);
        if (ans != 0) ans.sign = !ans.sign;
        return ans;
    }

    // substract
    BigInteger operator-(const BigInteger& b) const {
        if (!b.sign) { return *this + (-b); }
        if (!sign) { return -((-*this) + b); }
        if (*this < b) { return -(b - *this); }
        BigInteger ans;
        ans.num.clear();
        for (int i = 0, g = 0;; i++) {
            int sz = static_cast<int>(num.size());
            int b_sz = static_cast<int>(b.num.size());
            if (g == 0 && i >= sz && i >= b_sz) break;
            int x = g;
            g = 0;
            if (i < sz) x += num[i];
            if (i < b_sz) x -= b.num[i];
            if (x < 0) {
                x += BASE;
                g = -1;
            }
            ans.num.push_back(x);
        }
        ans.setLength();
        return ans;
    }

    // multiply
    BigInteger operator*(const BigInteger& b) const {
        int lena = num.size(), lenb = b.num.size();
        std::vector<long long> ansLL;
        for (int i = 0; i < lena + lenb; i++) ansLL.push_back(0);
        for (int i = 0; i < lena; i++) {
            for (int j = 0; j < lenb; j++) {
                ansLL[i + j] += (long long)num[i] * (long long)b.num[j];
            }
        }
        while (ansLL.back() == 0 && ansLL.size() != 1) ansLL.pop_back();
        int len = ansLL.size();
        long long g = 0, tmp;
        BigInteger ans;
        ans.sign = (ansLL.size() == 1 && ansLL[0] == 0) || (sign == b.sign);
        ans.num.clear();
        for (int i = 0; i < len; i++) {
            tmp = ansLL[i];
            ans.num.emplace_back((tmp + g) % BASE);
            g = (tmp + g) / BASE;
        }
        if (g > 0) ans.num.emplace_back(g);
        ans.setLength();
        return ans;
    }

    // divide
    BigInteger operator/(const long long& b) const {
        BigInteger c;
        c.num.clear();
        for (size_t i = 0; i < num.size(); i++) {
            c.num.push_back(0);
        }
        long long g = 0;
        for (size_t i = num.size() - 1; i >= 0; i--) {
            c.num[i] = int((num[i] + g * BASE) / b);
            g = num[i] + g * BASE - c.num[i] * b;
        }
        for (int i = num.size() - 1; c.num[i] == 0; i--) {
            c.num.pop_back();
        }
        return c;
    }

    // divide BigInteger
    BigInteger operator/(const BigInteger& b) const {
        BigInteger aa((*this).abs());
        BigInteger bb(b.abs());
        if (aa < bb) return 0;
        char* str = new char[aa.size() + 1];
        memset(str, 0, sizeof(char) * (aa.size() + 1));
        BigInteger tmp;
        int lena = aa.length, lenb = bb.length;
        for (int i = 0; i <= lena - lenb; i++) {
            tmp = bb.e(lena - lenb - i);
            while (aa >= tmp) {
                ++str[i];
                aa = aa - tmp;
            }
            str[i] += '0';
        }
        BigInteger ans(str);
        delete[]str;
        ans.sign = (ans == 0 || sign == b.sign);
        return ans;
    }

    // modules
    BigInteger operator%(const long long& b) const {
        long long ans = 0;
        for (int i = num.size() - 1; i >= 0; i--)
            ans = (ans * BASE + num[i]) % b;
        return ans;
    }

    // modules BigInteger
    BigInteger operator%(const BigInteger& b) const {
        return *this - *this / b * b;
    }

    BigInteger& operator++() {
        *this = *this + 1;
        return *this;
    }
    BigInteger& operator--() {
        *this = *this - 1;
        return *this;
    }
    BigInteger& operator+=(const BigInteger& b) {
        *this = *this + b;
        return *this;
    }
    BigInteger& operator-=(const BigInteger& b) {
        *this = *this - b;
        return *this;
    }
    BigInteger& operator*=(const BigInteger& b) {
        *this = *this * b;
        return *this;
    }
    BigInteger& operator/=(const long long& b) {
        *this = *this / b;
        return *this;
    }
    BigInteger& operator/=(const BigInteger& b) {
        *this = *this / b;
        return *this;
    }
    BigInteger& operator%=(const long long& b) {
        *this = *this % b;
        return *this;
    }
    BigInteger& operator%=(const BigInteger& b) {
        *this = *this % b;
        return *this;
    }

    bool operator<(const BigInteger& b) const {
        if (sign && !b.sign) { return false; }
        else if (!sign && b.sign) { return true; }
        else if (!sign && !b.sign) { return -b < -*this; }
        if (num.size() != b.num.size()) return num.size() < b.num.size();
        for (int i = num.size() - 1; i >= 0; i--)
            if (num[i] != b.num[i]) return num[i] < b.num[i];
        return false;
    }

    bool operator>(const BigInteger& b) const { return b < *this; }
    bool operator<=(const BigInteger& b) const { return !(b < *this); }
    bool operator>=(const BigInteger& b) const { return !(*this < b); }
    bool operator!=(const BigInteger& b) const { return b < *this || *this < b; }
    bool operator==(const BigInteger& b) const { return !(b < *this) && !(*this < b); }

    bool operator||(const BigInteger& b) const { return *this != 0 || b != 0; }
    bool operator&&(const BigInteger& b) const { return *this != 0 && b != 0; }
    bool operator!() { return (bool)(*this == 0); }

    friend std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
        if (!x.sign) out << '-';
        out << x.num.back();
        for (int i = static_cast<int>(x.num.size()) - 2; i >= 0; i--) {
            char buf[10];
            sprintf_s(buf, "%08d", x.num[i]);
            for (size_t j = 0; j < strlen(buf); j++) out << buf[j];
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, BigInteger& x) {
        std::string str;
        in >> str;
        size_t len = str.size();
        int start = 0;
        if (str[0] == '-') start = 1;
        if (str[start] == '\0') return in;
        for (size_t i = start; i < len; i++) {
            if (str[i] < '0' || str[i] > '9') return in;
        }
        x.sign = !start;
        x = str.c_str();
        return in;
    }
    BigInteger pow(int n) {
        BigInteger ans = 1, base = *this;
        while (n) {
            if (n & 1) ans = ans * base;
            base = base * base;
            n >>= 1;
        }
        return ans;
    }
};
BigInteger Factorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1 || n == 2) return n;
    std::vector<bool> u(n + 1, false);
    std::vector<std::pair<int, int>> p; // множители и их показатели степеней
    for (int i = 2; i <= n; ++i) {

        if (!u[i]) // если i - очередное простое число
        {
            // считаем показатель степени в разложении
            int k = n / i;
            int c = 0;
            while (k > 0)
            {
                c += k;
                k /= i;
            }
            // запоминаем множитель и его показатель степени
            p.push_back(std::pair<int, int>(i, c));
            // просеиваем составные числа через решето
            int j = 2;
            while (i * j <= n)
            {
                u[i * j] = true;
                ++j;
            }
        }
    }
    // вычисляем факториал
    vector<BigInteger> bis;

    for (int i = p.size() - 1; i >= 0; --i) {
        bis.push_back(BigInteger(p[i].first).pow(p[i].second));
    }
    BigInteger r = Concurrency::parallel_reduce(bis.begin() + 1, bis.end(), bis[0], [](auto fir, auto sec) { return fir * sec; });
    //BigInteger r = reduce(std::execution::par_unseq,bis.begin() + 1, bis.end(), bis[0], [](auto fir, auto sec) { return fir * sec; });
    return r;
}

void print_results(const char* const tag,
    const BigInteger& N,
    high_resolution_clock::time_point startTime,
    high_resolution_clock::time_point endTime) {
    //cout << "result: " << N << endl;
    printf("%s: Len: %lu Time: %fms\n",
        tag,
        N.size(),
        duration_cast<duration<double, milli>>(endTime - startTime).count()
    );
}

int main() {
#if 1
    printf("Testing with %zu!\n", testSize);
    vector<BigInteger> Integers(testSize);
    for (int i = 1; i <= testSize; ++i) {
        Integers[i - 1] = i;
    }
    for (int i = 0; i < iterationCount; ++i) {
        const auto startTime = high_resolution_clock::now();
        BigInteger res = Factorial(testSize);
        //BigInteger res = Factorial(Integers);
        const auto endTime = high_resolution_clock::now();
        print_results("ConcRt", res, startTime, endTime);
    }
#endif
    return 0;

}