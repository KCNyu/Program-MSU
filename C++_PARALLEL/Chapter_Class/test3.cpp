#include <iostream>
#include <omp.h> // NEW ADD

using namespace std;

#define DEFINE_idx auto idx = omp_get_thread_num();
#define _ROWS (omp_get_num_threads())

int main()
{
	#pragma omp parallel for num_threads(3)
	for(int i = 0; i < 10; i++)
	{
		DEFINE_idx;
		printf("- idx is %d, i is %d, total thread num is %d\n", idx, i, _ROWS);
	}
}