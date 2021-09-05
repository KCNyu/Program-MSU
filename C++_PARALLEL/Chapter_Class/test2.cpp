#include <iostream>
#include <omp.h> // NEW ADD

using namespace std;

int main()
{

	int sum = 0;
#pragma omp parallel for num_threads(32) reduction(+:sum)
	for (int i = 0; i < 100; i++)
	{
		sum += i;
	}

	cout << sum << endl;
	return 0;
}