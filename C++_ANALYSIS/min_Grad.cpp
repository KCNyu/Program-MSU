#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#define derta 0.000001

double f(double x, double y)
{
	return 10 * pow(y - x * x, 2) + pow(1 - x, 2);
}
double derivatives_x(function<double(double, double)> const &f, double x, double y)
{
	return (f(x + derta, y) - f(x, y)) / derta;
}
double derivatives_y(function<double(double, double)> const &f, double x, double y)
{
	return (f(x, y + derta) - f(x, y)) / derta;
}
double min_Grad(function<double(double, double)> const &f, double a, double b, double eps)
{
	double alpha = 0.01;
	pair<double, double> x = {a, b};
	pair<double, double> dx = {derivatives_x(f, x.first, x.second), derivatives_y(f, x.first, x.second)};

	double f_old = f(x.first, x.second);

	double f_result;
	while (true)
	{
		x.first -= alpha * dx.first;
		x.second -= alpha * dx.second;
		f_result = f(x.first, x.second);
		if (fabs(f_result - f_old) <= eps)
		{
			break;
		}
		dx.first = derivatives_x(f, x.first, x.second);
		dx.second = derivatives_y(f, x.first, x.second);
		f_old = f_result;
	}
	cout << fixed << setprecision(3) << "min_x = " << x.first << " min_y = " << x.second << endl;
	cout << "f_result = " << f_result << endl;
	return f_result;
}
int main(int argc, char const *argv[])
{
	min_Grad(f, 0, 2, 0.00000001);
	return 0;
}