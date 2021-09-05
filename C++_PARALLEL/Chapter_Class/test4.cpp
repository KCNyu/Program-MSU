#include <iostream>
#include <cmath>
#include <omp.h> // NEW ADD
#include <chrono>
#include "LogUtils.h"
#include "mymath.h"

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#define DEFINE_idx auto idx = omp_get_thread_num();
#define _ROWS (omp_get_num_threads())

int main()
{
	int cnt_ans = 0;
	int len = 252290;
	int v_i[len];
	for(int i = 0; i < len; i++){
		v_i[i] = random()%10000;
	}
	const auto startTime = high_resolution_clock::now();
#pragma omp parallel for reduction(+ \
				   : cnt_ans) default(shared) num_threads(8)
	for (int i = 0; i < len; i++)
	{
		auto &e = v_i[i];
		int t = 0;

		if (i < len / 2)
		{
			t = pow(e, 2);
		}
		else
		{
			t = (int)sqrt(e);
		}
		//cout << "t : " << t << endl;
		if (t % 2 == 1)
		{
			cnt_ans += 1;
		}
	}
	const auto endTime = high_resolution_clock::now();
	printf("Time: %fms\n", duration_cast<duration<double, milli>>(endTime - startTime).count());
	cout << omp_get_num_procs() << endl;
	LOG(2,"cnt_ans = %d\n",cnt_ans);
	LOG_INFO("cnt_ans = %d\n",cnt_ans);
}
