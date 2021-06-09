#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Supernumber {
    private:
        vector<int> num;
        int len = 0;

    public:
        Supernumber() = default;
        Supernumber(int n);
        Supernumber(string s);
        int Getlen() const { return len; }
        Supernumber operator*(const Supernumber &N);
        friend ostream &operator<<(ostream &os, const Supernumber &N);
};
Supernumber::Supernumber(int n) : len(n) { num.resize(len); }
Supernumber::Supernumber(string s) {
    len = s.size();
    num.resize(len);
    for (int i = 0; i < len; i++) {
        num[len - i - 1] = s[i] - '0';
    }
}
Supernumber Supernumber::operator*(const Supernumber &N) {
    Supernumber result(len + N.len);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < N.len; j++) {
            result.num[i + j] = num[i] * N.num[j] + result.num[i + j];
            result.num[i + j + 1] = result.num[i + j] / 10 + result.num[i + j + 1];
            result.num[i + j] = result.num[i + j] % 10;
        }
    }
    if (result.num[result.len - 1] == 0)
        result.len--;
    return result;
}
ostream &operator<<(ostream &os, const Supernumber &N) {
    int i = 0;
    while (i < N.len) {
        os << N.num[N.len - ++i];
    }
    os << endl;
    return os;
}
Supernumber Factorial(const vector<Supernumber>& sn) {
    Supernumber result("1");
    for (unsigned i = 0; i < sn.size(); i++) {
        result = result * sn[i];
    }
    return result;
}
#endif /* ifndef BIGINTEGER_H */
