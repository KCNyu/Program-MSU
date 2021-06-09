/*================================================================
 * Filename:SuperNumber_Exponent.cpp
 * Author: KCN_yu
 * Createtime:Sun 22 Mar 2020 11:53:36 AM CST
 ================================================================*/

#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#if 0
using std::vector;
using std::string;
using std::ostream;
using std::to_string;
using std::cout;
using std::endl;
using std::milli;
#endif

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
Supernumber Factorial(int N) {
    Supernumber result("1");
    for (int i = 1; i <= N; i++) {
        Supernumber tmp(to_string(i));
        result = result * tmp;
    }
    return result;
}
Supernumber Exponent(const Supernumber& N, int X){
    Supernumber result("1");
    if(X == 0){
        return result;
    }
    if(X == 1) return N;
    result = Exponent(N,X >> 1);
    result = result * result;
    if((X & 0x01) == 1) result = result * N;
    return result;
}
void print_results(const Supernumber &N,
        high_resolution_clock::time_point startTime,
        high_resolution_clock::time_point endTime) {
    cout << "result: " << N;
    printf("Len: %d Time: %fms\n",
            N.Getlen(),
            duration_cast<duration<double, milli>>(endTime - startTime).count());
}
int main(int argc, char *argv[]) {

    Supernumber N1("2");

    /*
    const auto startTime = high_resolution_clock::now();
    Supernumber N2 = Factorial(1000);
    const auto endTime = high_resolution_clock::now();
    print_results(N2, startTime, endTime);
    */
    cout << Exponent(N1,16);
    return 0;
}
