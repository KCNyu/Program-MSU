/*================================================================
 * Filename:SuperNumber_Exponent.cpp
 * Author: KCN_yu
 * Createtime:Sun 22 Mar 2020 11:53:36 AM CST
 ================================================================*/

#include <chrono>
#include <stdlib.h>
#include "BigInteger.h"

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

void print_results(const char* const tag,
    const Supernumber& N,
    high_resolution_clock::time_point startTime,
    high_resolution_clock::time_point endTime) {
    //cout << "result: " << N;
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
    for (int i = 0; i < iterationCount; ++i) {
        const auto startTime = high_resolution_clock::now();
        Supernumber res = Factorial(supernumbers);
        const auto endTime = high_resolution_clock::now();
        print_results("Serial", res, startTime, endTime);
    }
    return 0;
}
