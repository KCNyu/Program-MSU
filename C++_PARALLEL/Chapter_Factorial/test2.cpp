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
#include <algorithm>
#include <execution>
#include <ppl.h>


using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

const int iterationCount = 5;
const size_t testSize = 10000;

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
    int len;

public:
    Supernumber();
    Supernumber(int n);
    Supernumber(string s);
    int Getlen() const { return len; }
    Supernumber operator*(const Supernumber& N);
    friend Supernumber operator*(const Supernumber& N1, const Supernumber& N2);
    friend ostream& operator<<(ostream& os, const Supernumber& N);
};
Supernumber::Supernumber() : len(1) { num.resize(1); num[0] = 1; }
Supernumber::Supernumber(int n) : len(n) { num.resize(len); }
Supernumber::Supernumber(string s) {
    len = s.size();
    num.resize(len);
    for (int i = 0; i < len; i++) {
        num[len - i - 1] = s[i] - '0';
    }
}
Supernumber Supernumber::operator*(const Supernumber& N) {
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
Supernumber operator*(const Supernumber& N1, const Supernumber& N2) {
    Supernumber result(N1.len + N2.len);
    for (int i = 0; i < N1.len; i++) {
        for (int j = 0; j < N2.len; j++) {
            result.num[i + j] = N1.num[i] * N2.num[j] + result.num[i + j];
            result.num[i + j + 1] = result.num[i + j] / 10 + result.num[i + j + 1];
            result.num[i + j] = result.num[i + j] % 10;
        }
    }
    if (result.num[result.len - 1] == 0)
        result.len--;
    return result;
}
ostream& operator<<(ostream& os, const Supernumber& N) {
    int i = 0;
    while (i < N.len) {
        os << N.num[N.len - ++i];
    }
    os << endl;
    return os;
}

void print_results(const char* const tag,
    const Supernumber& N,
    high_resolution_clock::time_point startTime,
    high_resolution_clock::time_point endTime) {
    cout << "result: " << N;  
    printf("%s: Len: %d Time: %fms\n",
        tag,
        N.Getlen(),
        duration_cast<duration<double, milli>>(endTime - startTime).count()
    );
}
int main() {
    printf("Testing with %zu!\n", testSize);
    vector<Supernumber> supernumbers(testSize);
    for(int i = 1; i <= testSize; ++i) {
        supernumbers[i-1] = Supernumber(to_string(i));
    }
    for (int i = 0; i < 1; ++i) {
        const auto startTime = high_resolution_clock::now();
        Supernumber res = reduce(std::execution::par_unseq, supernumbers.begin()+1, supernumbers.end(), supernumbers[0], [](auto fir, auto sec) { return fir * sec; });
        const auto endTime = high_resolution_clock::now();
        print_results("Parallel", res, startTime, endTime);
    }
    return 0;
}