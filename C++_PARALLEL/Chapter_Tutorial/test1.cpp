#include <iostream>
using namespace std;

int main()
{
#pragma omp parallel
	{
		cout << "All thread run this" << endl;
#pragma omp sections
		{
#pragma omp section
			{
				cout << "this excute in parallel" << endl;
			}
#pragma omp section
			{
				cout << "Sequential statement 1" << endl;
				cout << "This always excute after statement 1" << endl;
			}
#pragma omp section
			{
				cout << "this also excute in prallel" << endl;
			}
		}
	}
}