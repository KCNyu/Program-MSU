#define GL_SILENCE_DEPRECATION

#include <cmath>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <chrono>
#include <GLUT/GLUT.h>
#include <iomanip>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

using vec_d = vector<double>;
using matr_d = vector<vector<double>>;

inline matr_d plus1(const matr_d &m1, const matr_d &m2)
{
	matr_d res(m1.size());
	for (size_t i = 0; i < m1.size(); i++)
	{
		res[i].resize(m1[0].size());
		for (size_t j = 0; j < m1[0].size(); j++)
		{
			res[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return res;
}
inline matr_d dot(const matr_d &m1, const matr_d &m2)
{
	matr_d res(m1.size());
	for (size_t i = 0; i < m1.size(); i++)
	{
		res[i].resize(m2[0].size());
		for (size_t j = 0; j < m2[0].size(); j++)
		{
			double sum = 0;
			for (size_t k = 0; k < m1[0].size(); k++)
			{
				sum += m1[i][k] * m2[k][j];
			}
			res[i][j] = sum;
		}
	}
	return res;
}
inline matr_d dot(const matr_d &m, const double num)
{
	matr_d res(m.size());
	for (size_t i = 0; i < m.size(); i++)
	{
		res[i].resize(m[0].size());
		for (size_t j = 0; j < m[0].size(); j++)
		{
			res[i][j] = m[i][j] * num;
		}
	}
	return res;
}
matr_d inverse(const matr_d &m)
{
	const double EPS = 0.0000000001;
	matr_d tmp = m;
	size_t sz = tmp.size();
	matr_d res;
	res.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res[i].resize(sz);
		res[i][i] = 1;
	}
	for (int i = 0; i < sz - 1; i++)
	{
		for (int j = i + 1; j < sz; j++)
		{
			if (tmp[i][i] < EPS && tmp[i][i] > -1 * EPS)
			{
				bool flag = true;
				for (int m = i + 1; m < sz; m++)
				{
					if (tmp[m][i] < EPS && tmp[m][i] > -1 * EPS)
						continue;
					else
					{
						swap(tmp[i], tmp[m]);
						swap(res[i], res[m]);
						flag = false;
					}
				}
				if (flag)
					throw "Doesn't have result!\n";
			}
			double temp = tmp[j][i] / tmp[i][i];
			for (int k = 0; k < sz; k++)
			{
				tmp[j][k] -= tmp[i][k] * temp;
				res[j][k] -= res[i][k] * temp;
			}
		}
	}
	for (int i = 0; i < sz; i++)
	{
		double first = tmp[i][i];
		for (int j = 0; j < sz; j++)
		{
			tmp[i][j] /= first;
			res[i][j] /= first;
		}
	}
	for (int i = sz - 1; i > 0; i--)
	{
		for (int j = 0; j <= i - 1; j++)
		{
			double temp = tmp[j][i] / tmp[i][i];
			for (int k = 0; k < sz; k++)
			{
				tmp[j][k] -= tmp[i][k] * temp;
				res[j][k] -= res[i][k] * temp;
			}
		}
	}
	return res;
}
// Integral
double trapezoid(double a, double b, function<double(double)> f)
{
	return (f(a) + f(b)) * (b - a) / 2;
}
double integral_help(double a, double b, double eps, double A, function<double(double)> f)
{
	double c = a + (b - a) / 2;
	double L = trapezoid(a, c, f), R = trapezoid(c, b, f);
	if (fabs(L + R - A) <= eps)
		return L + R + (L + R - A);
	return integral_help(a, c, eps, L, f) + integral_help(c, b, eps, R, f);
}
double integral(function<double(double)> f, double a, double b, double eps)
{
	return integral_help(a, b, eps, trapezoid(a, b, f), f);
}
double trapezoid(double a, double b, function<double(double, double)> const &f, double y)
{
	return (f(a, y) + f(b, y)) * (b - a) / 2;
}
double integral_help(double a, double b, double eps, double A, function<double(double, double)> const &f, double y)
{
	double c = a + (b - a) / 2;
	double L = trapezoid(a, c, f, y), R = trapezoid(c, b, f, y);
	if (fabs(L + R - A) <= eps)
		return L + R + (L + R - A);
	return integral_help(a, c, eps, L, f, y) + integral_help(c, b, eps, R, f, y);
}
double integral(function<double(double, double)> const &f, double a, double b, double c, double d, double eps)
{
	auto f_i = [&](double c)
	{ return integral_help(a, b, eps, trapezoid(a, b, f, c), f, c); };
	return integral(f_i, c, d, eps);
}

class Integral_equation
{
private:
	double a;
	double b;
	const int n;
	double lambda;
	static double K(double x, double s);
	double f(double x);
	double fi(double x, double m);
	double psi(double x, double m);

	matr_d A;
	matr_d B;
	matr_d C;
	const double step = 0.01;
	const double eps = 0.000001;

public:
	Integral_equation(const double a, const double b, const double lambda, const int n);
	void Solve();
	void Print();
	void Print(const char index);
	double Spline(double x);
	matr_d x;
	matr_d y;
	int sz;
	~Integral_equation() {}
};

Integral_equation::Integral_equation(const double a, const double b, const double lambda, const int n) : a(a),
													 b(b),
													 lambda(lambda),
													 n(n)
{
	A.resize(n);
	B.resize(n);

	sz = (b - a) / step;
	x.resize(sz);
	y.resize(sz);

	for (size_t i = 0; i < n; i++)
	{
		A[i].resize(n);
		B[i].resize(1);
	}
	for (size_t i = 0; i < sz; i++)
	{
		x[i].resize(1);
		y[i].resize(1);
		x[i][0] = a + step * i;
		y[i][0] = f(x[i][0]);
	}
}
double Integral_equation::K(double x, double s)
{
	return fabs(x - s);
}
double Integral_equation::f(double x)
{
	return pow(x, 3);
}
double Integral_equation::fi(double x, double m)
{
	return pow(x, m);
}
double Integral_equation::psi(double x, double m)
{
	return pow(x, m - 1);
}
void Integral_equation::Solve()
{

	for (size_t j = 0; j < n; j++)
	{
		auto curride_K_1 = [&](double j)
		{
			return [&, j](double x, double s)
			{ return psi(x, j + 1) * f(s) * K(x, s); };
		};
		B[j][0] = integral(curride_K_1(j), a, b, a, b, eps);
		for (size_t i = 0; i < n; i++)
		{
			auto curride_K_2 = [&](double i, double j)
			{
				return [&, i, j](double x, double s)
				{ return psi(x, j + 1) * fi(s, i + 1) * K(x, s); };
			};
			auto func = [&](double x)
			{
				return fi(x, i + 1) * psi(x, j + 1);
			};
			A[i][j] = integral(func, a, b, eps) - lambda * integral(curride_K_2(i, j), a, b, a, b, eps);
		}
	}
	C = dot(inverse(A), B);

	matr_d x_fi(sz);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < sz; j++)
		{
			x_fi[j].resize(1);
			x_fi[j][0] = fi(x[j][0], i + 1);
		}
		y = plus1(y, dot(x_fi, C[i][0]));
	}
}
double Integral_equation::Spline(double p)
{
	vec_d h(sz), s(sz), F(sz);
	matr_d m(sz);
	for (size_t i = 0; i < sz; i++)
	{
		m[i].resize(sz);
	}
	for (size_t i = sz - 1; i > 0; i--)
	{
		F[i] = (y[i][0] - y[i - 1][0]) / (x[i][0] - x[i - 1][0]);
		h[i - 1] = x[i][0] - x[i - 1][0];
	}
	for (size_t i = 1; i < sz - 1; i++)
	{
		m[i][i] = 2 * (h[i - 1] + h[i]);
		if (i != 1)
		{
			m[i][i - 1] = h[i - 1];
			m[i - 1][i] = h[i - 1];
		}
		m[i][n - 1] = 6 * (F[i + 1] - F[i]);
	}

	for (size_t i = 1; i < sz - 2; i++)
	{
		double temp = (m[i + 1][i] / m[i][i]);
		for (size_t j = 1; j <= sz - 1; j++)
			m[i + 1][j] -= temp * m[i][j];
	}

	for (size_t i = sz - 2; i > 0; i--)
	{
		double sum = 0;
		for (size_t j = i; j <= sz - 2; j++)
			sum += m[i][j] * s[j];
		s[i] = (m[i][sz - 1] - sum) / m[i][i];
	}
	double res = 0;
	for (size_t i = 0; i < sz - 1; i++)
	{
		if (x[i][0] <= p && p <= x[i + 1][0])
		{
			double a1 = (s[i + 1] - s[i]) / (6 * h[i]);
			double b1 = s[i] / 2;
			double c1 = (y[i + 1][0] - y[i][0]) / h[i] - (2 * h[i] * s[i] + s[i + 1] * h[i]) / 6;
			double d1 = y[i][0];
			res = a1 * pow((p - x[i][0]), 3) + b1 * pow((p - x[i][0]), 2) + c1 * (p - x[i][0]) + d1;
		}
	}
	return res;
}
void Integral_equation::Print(const char index)
{
	matr_d *matr = nullptr;
	switch (index)
	{
	case 'A':
		matr = &A;
		break;
	case 'B':
		matr = &B;
		break;
	case 'C':
		matr = &C;
		break;
	case 'y':
		matr = &y;
		break;
	default:
		break;
	}

	string indexline = "=========MATR_";
	indexline += index;
	indexline += "========\n[";

	cout << indexline;
	for (int i = 0; i < matr->size(); i++)
	{
		if (i != 0)
		{
			cout << " ";
		}
		for (int j = 0; j < (*matr)[0].size(); j++)
		{
			cout.width(10);
			cout << fixed << setprecision(3) << (*matr)[i][j] << " ";
		}
		if (i < matr->size() - 1)
		{
			cout << ";" << endl;
		}
		else
		{
			cout << "]" << endl;
		}
	}
}

void Integral_equation::Print()
{
	Print('A');
	Print('B');
	Print('C');
	Print('y');
}

Integral_equation eq(0, 1, 1, 3);

void Display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	for (double i = 0; i <= 0.9; i += 0.01)
		glVertex2f(i, eq.Spline(i));
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	for (size_t i = 0; i < eq.sz; i++)
		glVertex2f(eq.x[i][0], eq.y[i][0]);
	glEnd();
	glFlush(); //更新窗口
}
void PrintTime(high_resolution_clock::time_point start_time,
	       high_resolution_clock::time_point end_time)
{
	cout << "Time: "
	     << duration_cast<duration<double, milli>>(end_time - start_time).count()
	     << " ms" << endl;
}
int main(int argc, char *argv[])
{
	const auto start_time = high_resolution_clock::now();
	eq.Solve();
	eq.Print();
	const auto end_time = high_resolution_clock::now();
	PrintTime(start_time, end_time);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(1000, 1000);
	glutInitWindowSize(400, 400);
	glutCreateWindow("graph");
	glutDisplayFunc(&Display);
	glutMainLoop();

	return 0;
}