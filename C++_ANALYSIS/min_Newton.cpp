#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <chrono>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#define derta 0.000001

double f(double x)
{
	return 2 * x - 1.0 + 2 * cos(M_PI * x);
}
double derivatives_1(function<double(double)> const &f, double x)
{
	return (f(x + derta) - f(x)) / derta;
}
double derivatives_2(function<double(double)> const &f, double x)
{
	return (derivatives_1(f, x + derta) - derivatives_1(f, x)) / derta;
}
double min_Newton(function<double(double)> const &f, double a, double b, double eps)
{
	double x1 = (a + b) / 2.0;
	double x2 = x1 - derivatives_1(f, x1) / derivatives_2(f, x1);
	while (fabs(x2 - x1) > eps)
	{
		x1 = x2;
		x2 = x1 - derivatives_1(f, x1) / derivatives_2(f, x1);
	}
	return x2;
}
void PrintTime(high_resolution_clock::time_point start_time,
	       high_resolution_clock::time_point end_time)
{
	cout << "Time: "
	     << duration_cast<duration<double, milli>>(end_time - start_time).count()
	     << " ms" << endl;
}
void test(double eps)
{
	const auto start_time = high_resolution_clock::now();
	double min_x = min_Newton(f, 0, 2, eps);
	double min = f(min_x);
	const auto end_time = high_resolution_clock::now();
	cout << "min_x = " << min_x << endl;
	cout << "min = " << min << endl;
	PrintTime(start_time, end_time);
}
int main(int argc, char const *argv[])
{
	test(0.000001);
	return 0;
}
